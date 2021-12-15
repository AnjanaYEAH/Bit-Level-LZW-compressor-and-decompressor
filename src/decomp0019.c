
#include <stdlib.h>
#include <stdio.h>
struct node2{
  unsigned long key;
  unsigned long data;
  unsigned long codeLength; // how many bits the code the key is representing is
  unsigned char keyLength;
  struct node2* next;
  struct node2* previous;
};
struct node2* head2;
struct node2* end2;
unsigned long keyCount2 = 0;
unsigned char keyLength2 = 3;
unsigned long numberOfKeys;
unsigned long keysRemaining;
unsigned int power22(unsigned int a){
    int initial = 1;
    while(a){
        initial *= 2;
        a--;
    }
    return initial;
}

void insertAtEnd2(unsigned long key, unsigned long data, unsigned long codeLength, unsigned char keyLength){
    struct node2* newn = (struct node2*)malloc(sizeof(struct node2));
    newn -> key = key;
    newn -> data = data;
    newn -> codeLength = codeLength;
    newn -> keyLength = keyLength;
    newn -> next = end2;

    struct node2* oneBeforeEnd = end2 -> previous;
    oneBeforeEnd -> next = newn;
    end2 -> previous = newn;
    keyCount2++;
    numberOfKeys--;
}
unsigned int lookUp2(unsigned long key, unsigned long keyLength){
    struct node2* temp = head2->next;
    while(temp->codeLength){
        if(temp -> key == key && temp -> keyLength == keyLength){return 1;}
        temp = temp -> next;
    }
    return 0;
}


struct node2* output2(unsigned long key, unsigned long keyLength){
    struct node2* temp = head2->next;
    while(temp->codeLength){
        if(temp -> key == key && temp -> keyLength == keyLength){return temp;}
        temp = temp -> next;
    }
    return NULL;
    
}


void createTable2(){
    head2 = (struct node2*)malloc(sizeof(struct node2));
    end2 = (struct node2*)malloc(sizeof(struct node2));
    
    head2 -> next = end2;
    head2 -> codeLength = 0;
    head2 -> previous = NULL;

    end2 -> previous = head2;
    end2 -> codeLength = 0;
    end2 -> next = NULL;
    
    for(int i = 0; i<4; i++){
        insertAtEnd2(i, i, 2, keyLength2);
    }
}


unsigned char bitmask(unsigned char a){
    int total = 0;
    for(int i = 0; i<a; i++){
        total += power22(i);
    }
    return total;
}

unsigned char reverseBitmask(unsigned char a){
    int total = 0;
    for(int i = 0; i<a; i++){
        total += power22(7-i);
    }
    return total;
}
void Decode(FILE* in_file, FILE* out_file) {
  // Code goes here.
    createTable2();
    numberOfKeys = power22(keyLength2) - 1;
    unsigned char* littleEndianSize = malloc(4*sizeof(unsigned char));
    unsigned char* size = malloc(4*sizeof(unsigned char));
    fread(littleEndianSize, 4, 1, in_file);
    fwrite(littleEndianSize, 4, 1, out_file);

    //convert from little endian to normal size
    for(int i = 0; i<4; i++){
        *(size + i) = *(littleEndianSize + 3 - i);
    }
    
    unsigned int x = (size[0] << 24) + (size[1] << 16) + (size[2] << 8) + (size[3] << 0);
    unsigned int padding = 0;
    if(x % 4 == 0){padding = 4;}
    if(x % 4 == 1){padding = 3;}
    if(x % 4 == 2){padding = 2;}
    if(x % 4 == 3){padding = 1;}
    printf("size: %d\n", x);

    unsigned char* data = malloc(1*sizeof(unsigned char));
    unsigned long* string = malloc(1*sizeof(unsigned long));
    unsigned char stringCodeLength = 0;
    unsigned char* base = malloc(1*sizeof(unsigned char));
    int baseSize = 8;
    unsigned char* temp = malloc(1*sizeof(unsigned char));
    *(temp) = 0;

    

    unsigned int counter = 0;
    int byte = 8;
    int remainder = 0;
    unsigned char* outputByte = malloc(sizeof(unsigned char));
    int outputByteSpace = 8;
    unsigned char mask = 0;
    int shift = 0;
    unsigned long codeLength = 0;
    unsigned long* d = malloc(sizeof(unsigned long));
    struct node2* out = malloc(sizeof(struct node2));
    *(outputByte) = 0;
    keysRemaining = numberOfKeys - keyCount2;
    printf("number of Keys %d\n", keyCount2);
    printf("unused keys %d\n", keysRemaining);
    int firstRun = 1;
    
    int m = 0;
    int y = 0;
    while(fread(data, 1, 1, in_file) && x){

    if(firstRun){
        *(base) = *(data) & 224; //0b11100000
        *(base) = *(base) >> 5;
        printf("base: %d\n", *(base));
        out = output2(*(base), keyLength2);
        *(d) = out->data;
        codeLength = out->codeLength;
        printf("codeLength: %d\n", codeLength);

        int offset = outputByteSpace - codeLength;
        *(temp) = *(d);
        *(temp) = *(temp) << offset;
        *(outputByte) = *(outputByte) | *(temp);
        printf("outputByte: %d\n", *(outputByte));
        outputByteSpace -= codeLength;
        *(string) = *(d); // this simulates the string = table[code] before look starts
        stringCodeLength = codeLength;

        byte -= keyLength2;
        x -= codeLength/2;
    }
    if(x <= 0){
        printf("outputByte: %d\n", *(outputByte));
        fwrite(outputByte, 1, 1, out_file);
        break;
    }
    firstRun = 0;
        if(remainder){
            //remainder = 0;
            printf("rem: rem: %d\n", remainder);
            byte -= remainder;
            printf("rem: byte: %d\n", byte);
            mask = reverseBitmask(remainder);
            printf("rem: mask: %d\n", mask);
            printf("rem: data: %d\n", *(data));
            *(temp) = *(data)&mask;
            *(temp) = *(temp) >> (8-remainder);
            printf("rem: base: %d\n", *(base));
            printf("rem: temp: %d\n", *(temp));
            *(base) = *(temp) | *(base);
           // printf("rem: base: %d\n", *(base));
            printf("rem: keyLength: %d\n", keyLength2);
            if(lookUp2(*(base), keyLength2)){
                out = output2(*(base), keyLength2);
                printf("rem: base (in table): %d\n", *(base));
                codeLength = out -> codeLength;
                //stringCodeLength = codeLength;
                if(codeLength < 8){
                    int offset = outputByteSpace - codeLength;
                    if(offset < 0){
                        offset = -offset;
                        *(d) = out -> data;
                        *(temp) = *(d);
                        *(temp) = *(temp) >> (offset);
                        *(outputByte) = *(outputByte) | *(temp);
                        fwrite(outputByte, 1, 1, out_file);
                        *(outputByte) = 0;
                        outputByteSpace = 8;
                        int newOffset = outputByteSpace - offset;
                        *(temp) = *(d);
                        *(temp) = *(temp) << (newOffset);
                        *(outputByte) = *(outputByte) | *(temp);
                            
                    }else{
                            *(d) = out -> data;
                            *(temp) = *(d);
                            unsigned char add = *(string) << stringCodeLength;
                            add = add | *(temp);
                            printf("rem: else temp: %d\n", *(temp));
                            *(temp) = *(temp) << (offset);
                            
                            *(outputByte) = *(outputByte) | *(temp);
                            insertAtEnd2(keyCount2, add, stringCodeLength + 2, keyLength2);
                            //remember to add string + entry to translation table;
                            printf("rem: else outputByte: %d\n", *(outputByte));
                            *(string) = *(d);
                            outputByteSpace -= codeLength;
                            printf("rem: else codeLength: %d\n", codeLength);
                            printf("rem: else outputByteSpace: %d\n", outputByteSpace);
                            //insertAtEnd2();
                            x -= codeLength/2;
                            printf("x: %d\n", x);
                        }

                    
                }else{
                    printf("rem: if it is herer then once again it means there is too many byte");
                }
            }else{
                     int offset = outputByteSpace - (stringCodeLength);
                    if(offset <0){
                    printf("rem: noooooooooooooooooooooooooooooooo");
                    }else{
                        *(temp) = (*(string) << 2) | (*(string) & bitmask(2)) << offset;
                        printf("rem: temp: %d\n", *(temp));
                    }
                    
                    printf("rem: string: %d\n", *(string));
                    printf("rem: stringCodeLength: %d\n", stringCodeLength);
                    
                    
                    *(outputByte) = *(outputByte) | *(temp);
                    outputByteSpace -= stringCodeLength + 2;
                    printf("rem: outputByteSpace: %d\n", outputByteSpace);
                    //printf("outputByte: %d\n", *(outputByte));
                    insertAtEnd2(keyCount2,(*(string) << 2) | (*(temp) & bitmask(2)),stringCodeLength, keyLength2);
                    *(string) = *(temp);
                    stringCodeLength += 2;
                    x -= stringCodeLength/2;
            }
            
        }
        while(byte>0){
            if(x <= 0){
                break;
            }
            mask = bitmask(keyLength2);
            // printf("mask: %d\n", mask);
            shift = byte - keyLength2;
            // printf("shift: %d\n", shift);
            if(shift<0){
                printf("troubllleeeeeeeeeeeeeee\n");
                shift = -shift;
                remainder = shift;
                mask = mask >> shift;
                *(base)= *(data) & mask;
                *(base)= *(base) << shift;
                //we don't do code here, the code for here is in rembase
            }else{
                remainder = 0;
                printf("gooodnesssssssssssssss\n");
                mask = mask << shift;
                *(base)= *(data) & mask;
                *(base)= *(base) >> shift;
                //only check if the base exists in the table within here because this is where the full formed bases are
                printf("base: %d\n", *(base));
                printf("keyLength: %d\n", keyLength2);
                if(lookUp2(*(base), keyLength2)){
                    
                    out = output2(*(base), keyLength2);
                    printf("base (in table): %d\n", *(base));
                    codeLength = out -> codeLength;
                    //stringCodeLength = codeLength;
                    if(codeLength < 8){
                        int offset = outputByteSpace - codeLength;
                        if(offset < 0){
                            offset = -offset;
                            *(d) = out -> data;
                            *(temp) = *(d);
                            *(temp) = *(temp) >> (offset);
                            *(outputByte) = *(outputByte) | *(temp);
                            fwrite(outputByte, 1, 1, out_file);
                            *(outputByte) = 0;
                            outputByteSpace = 8;
                            int newOffset = outputByteSpace - offset;
                            *(temp) = *(d);
                            *(temp) = *(temp) << (newOffset);
                            *(outputByte) = *(outputByte) | *(temp);
                            
                        }else{
                            *(d) = out -> data;
                            *(temp) = *(d);
                            unsigned char add = *(string) << stringCodeLength;
                            add = add | *(temp);
                            printf("else temp: %d\n", *(temp));
                            *(temp) = *(temp) << (offset);
                            
                            *(outputByte) = *(outputByte) | *(temp);
                            printf("else keyLen: %d\n", keyCount2);
                            insertAtEnd2(keyCount2, add, stringCodeLength + 2, keyLength2);
                            //remember to add string + entry to translation table;
                            printf("else outputByte: %d\n", *(outputByte));
                            *(string) = *(d);
                            outputByteSpace -= codeLength;
                            printf("else codeLength: %d\n", codeLength);
                            printf("else outputByteSpace: %d\n", outputByteSpace);
                            //insertAtEnd2();
                            x -= codeLength/2;
                            printf("x: %d\n", x);
                        }

                    
                    }else{
                        // strill not accomodated for outputBytes that have been filled partially and then we swap to a big code
                        // and we dont acount for it here.
                         printf("how is it even possible to be this longgggggggggg");
                        // unsigned long counter = 0;
                        // int offset = 64 - codeLength;
                        // *(d) = out -> data
                        // //*(temp) = *(d) << offset;
                        // while(counter + 8 < codeLength){// counter of number of full
                        //     *(temp) = *(temp) >> (54 - counter);
                        //     fwrite(temp, 1, 1, out_file);
                        //     counter += 8;
                        // }
                        // counter += 8;
                        // *(temp) = *(temp) >> (54 - counter);
                        // //*(outputByte)
                    }
                        
                }else{
                    int offset = outputByteSpace - (stringCodeLength);
                    if(offset <0){
                    printf("noooooooooooooooooooooooooooooooo");
                    }else{
                        *(temp) = (*(string) << 2) | (*(string) & bitmask(2)) << offset;
                    }
                    
                    printf("string: %d\n", *(string));
                    printf("stringCodeLength: %d\n", stringCodeLength);
                    
                    
                    *(outputByte) = *(outputByte) | *(temp);
                    outputByteSpace -= stringCodeLength + 2;
                    printf("outputByteSpace: %d\n", outputByteSpace);
                    //printf("outputByte: %d\n", *(outputByte));
                    insertAtEnd2(keyCount2,(*(string) << 2) | (*(temp) & bitmask(2)),stringCodeLength, keyLength2);
                    printf("added to table: %d", (*(string) << 2) | (*(temp) & bitmask(2)));
                    *(string) = *(temp);
                    stringCodeLength += 2;
                    x -= stringCodeLength/2;

        
                    
                }
            }
            // printf("mask shift: %d\n", mask);
            byte-=keyLength2;
            //dont worry about the negatives because the next if(remainder) takes care of it by subtracting the right amount of bits.
            //only increment the keyCount if a new key is discovered that doesnt exist on the table
            // keyCount2++;
            keysRemaining = numberOfKeys - keyCount2;
            if(!keysRemaining){printf("we are out of keys need to expand to 4 bit codes\n");}
        }
        if(x == 0){
        printf("outputByte: %d\n", *(outputByte));
        fwrite(outputByte, 1, 1, out_file);
        *(outputByte) = 0;
        outputByteSpace = 8;
        break;
    }
        byte = 8;
    }
    *(data) = 0;
    if(x<=0){
        //printf("Invalid decoder input: %d %d %d %d %d \n", *(littleEndianSize), *(littleEndianSize + 1), *(littleEndianSize + 2), *(littleEndianSize + 3), *(data));
    }
    if(firstRun){
        //printf("Invalid decoder input: %d %d %d %d \n", *(littleEndianSize), *(littleEndianSize + 1), *(littleEndianSize + 2), *(littleEndianSize + 3));
    }
    keyCount2 = 0;
    keyLength2 = 3;
    numberOfKeys = 0;
    keysRemaining = 0;
    
    free(base);
    free(string);
    free(littleEndianSize);
    free(size);
    free(outputByte);
    free(d);
    free(data);
    
    struct node2* tempz = head2;
    struct node2* temp2;
    while(tempz){
        //you can free head and end becuase a new table is created with a new head and end
        temp2 = tempz;
        tempz = tempz -> next;
        free(temp2);
    }
}
