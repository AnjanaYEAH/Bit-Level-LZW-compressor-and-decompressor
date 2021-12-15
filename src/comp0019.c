#include <stdlib.h>
#include <stdio.h>

struct node{
  unsigned long key;
  unsigned long data;
  unsigned long codeLength; // how many bits the code the key is representing is
  unsigned char keyLength;
  struct node* next;
  struct node* previous;
};

struct node* head;
struct node* end;
unsigned int nodeCount = 0;
unsigned char keyLength = 3;




void insertAtEnd(unsigned long key, unsigned long data, unsigned long codeLength, unsigned char keyLength){
    struct node* newn = (struct node*)malloc(sizeof(struct node));
    newn -> key = key;
    newn -> data = data;
    newn -> codeLength = codeLength;
    newn -> keyLength = keyLength;
    newn -> next = end;

    struct node* oneBeforeEnd = end -> previous;
    oneBeforeEnd -> next = newn;
    end -> previous = newn;
    nodeCount++;
}
unsigned int lookUp(unsigned long data, unsigned long codeLength){
    struct node* temp = head->next;
    while(temp->codeLength){
        if(temp -> data == data && temp -> codeLength == codeLength){return 1;}
        temp = temp -> next;
    }
    return 0;
}


struct node* output(unsigned long data, unsigned long codeLength){
    struct node* temp = head->next;
    while(temp->codeLength){
        if(temp -> data == data && temp -> codeLength == codeLength){return temp;}
        temp = temp -> next;
    }
    return NULL;
    
}


void createTable(){
    head = (struct node*)malloc(sizeof(struct node));
    end = (struct node*)malloc(sizeof(struct node));
    
    head -> next = end;
    head -> codeLength = 0;
    head -> previous = NULL;

    end -> previous = head;
    end -> codeLength = 0;
    end -> next = NULL;
    
    for(int i = 0; i<4; i++){
        insertAtEnd(i, i, 2, keyLength);
    }
}

unsigned int power2(unsigned int a){
    int initial = 1;
    while(a){
        initial *= 2;
        a--;
    }
    return initial;
}


void Encode(FILE* in_file, FILE* out_file) {
  //Code goes here.
    createTable();
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

    

    unsigned int counter = 0;
    unsigned int byte = 0;
    unsigned char* outputByte = malloc(sizeof(unsigned char));
    unsigned char* outputPadding = malloc(sizeof(unsigned char));
    *(outputPadding) = 0;
    *(outputByte) = 0;
    while(fread(data, 1, 1, in_file) && x){
        printf("whole byte being read: %d\n", *(data));
        // *(data) = 233;
        // x = 4;
        if(!counter){
            *(string) = (unsigned long)(*(data) & ~63)>>6;
            stringCodeLength += 2;
            printf("string (first two bits): %d\n", *(string));
            int offset = 8 - 3 - byte;
            x--;
            if(x == 0){
                *(string) = *(string) << offset;
                fwrite(string, 1, 1, out_file);
                break;
            }
        }
        for(int i = 0; i<4; i++){
            if(x == 0){
                counter = 0;
                break;
            }
            if(i == 0 && counter){ // we dont want this to be accessed in the first byte first element of 2nd byte is okay
                *(base) = (*(data) & ~63)>>6;
                x--;
            }
            if(i == 1){ // i can only be 1 if there are more than 1 element left
                *(base) = (*(data) & ~207)>>4;
                x--;
            }
            if(i == 2){
                *(base) = (*(data) & ~243)>>2;
                x--;
            }
            if(i == 3){
                *(base) = *(data) & ~252;
                x--;
            }

            if(counter){
                unsigned long temp = *(string)<<2 | *(base);
                unsigned char tempCodeLength = stringCodeLength + 2;
                printf("base: %d\n", *(base));
                printf("string + base: %d\n", temp);
                printf("string + base length: %d\n", tempCodeLength);
                if (lookUp(temp, tempCodeLength)){
                    printf("aaaaa: shouldnt be here\n");
                    *(string) = temp;
                    stringCodeLength = tempCodeLength;
                    struct node* outputData = output(*(string), stringCodeLength);
                    if(outputData == NULL){
                        printf("aaaaa: not found\n");
                    }
                    unsigned char dkeyLength = outputData->keyLength;
                    unsigned char d = (unsigned char)outputData->key; //code that we are about to output
                    printf("aaaaa: dkeyLength %d\n", dkeyLength);
                    printf("aaaaa: d: %d\n", d);

                    if(byte + keyLength >8){ //if it is too big to fit all of it in current outputByte
                        printf("don't be here pleaseeeee\n");
                        if(x == 0){
                            int offset = 8 - keyLength - byte;
                            offset = -offset;
                            unsigned char dr = d >> offset;
                            printf("aaaaa: dr: %d\n", dr);
                            *(outputByte) = *(outputByte) | dr;
                            printf("aaaaa: output byte: %d\n", *(outputByte));
                            byte += (unsigned int)keyLength - offset;
                            if(byte == 8){
                                printf("mamamammamamamamama\n");
                                byte = 0;
                                fwrite(outputByte, 1, 1, out_file);
                                *(outputByte) = 0;
                                int newOffset = 8 - offset;
                                if(offset > 8 ){printf("sfsafdfdsfsadfssfsdfdssd");}
                                unsigned char dl = d << newOffset;
                                *(outputByte) = *(outputByte) | dl;
                                fwrite(outputByte, 1, 1, out_file);
                                byte += offset;
                            }
                        }
                    }else{
                        if(x == 0){
                            int offset = 8 - keyLength - byte;
                            printf("aaaaa: offset: %d\n", offset);
                            unsigned char dl = d << offset;
                            printf("aaaaa: dl: %d\n", dl);
                            printf("aaaaa: outputByte: %d\n", *(outputByte));
                            *(outputByte) = *(outputByte) | dl;
                            byte += keyLength;
                            fwrite(outputByte, 1, 1, out_file);
                        }
                    }
                    
                    
                }else{
                    struct node* outputData = output(*(string), stringCodeLength);
                    if(outputData == NULL){
                        printf("not found\n");
                    }
                    unsigned char dkeyLength = outputData->keyLength;
                    unsigned char d = (unsigned char)outputData->key; //code that we are about to output
                    printf("d: %d\n", d);
                    printf("keyLength: %d\n", keyLength);
                    printf("byte: %d\n", byte);
                    
                    if(byte + keyLength >8){ //if it is too big to fit all of it in current outputByte
                        if(byte <= 8){
                            printf("we need to split up the bytes\n");
                            int offset = 8 - keyLength - byte;
                            offset = -offset;
                            unsigned char dr = d >> offset;
                            printf("dr: %d\n", dr);
                            *(outputByte) = *(outputByte) | dr;
                            byte += (unsigned int)keyLength - offset;
                            insertAtEnd(nodeCount, temp, tempCodeLength, keyLength);

                            *(string) = *(base);
                            stringCodeLength = 2;
                            if(byte == 8){
                                byte = 0;
                                printf("output byte: %d\n", *(outputByte));
                                fwrite(outputByte, 1, 1, out_file);
                                *(outputByte) = 0;
                                int newOffset = 8 - offset;
                                if(offset > 8 ){printf("sfsafdfdsfsadfssfsdfdssddfsfsdfadfasdfdsfasfsdfadfasdfdfafadfasdfasdfa\n");}
                                unsigned char dl = d << newOffset;
                                *(outputByte) = *(outputByte) | dl;
                                byte += offset;
                                if(x == 0){
                                    if(nodeCount == power2(keyLength) + 1){
                                        keyLength++;
                                    }
                                    outputData = output(*(string), stringCodeLength);
                                    if(outputData == NULL){
                                        printf("not found\n");
                                    }
                                    dkeyLength = outputData->keyLength;
                                    d = (unsigned char)outputData->key; //code that we are about to output
                                    printf("d: %d\n", d);
                                    printf("byte: %d\n", byte);
                                    offset = 8 - keyLength - byte;
                                    printf("keyLength: %d\n", keyLength);
                                    printf("byte: %d\n", byte);
                                    if(offset<0){
                                        printf("whaaaat happppeeeeennnnnnndddd\n");
                                        offset = -offset;
                                        unsigned char dr = d >> offset;
                                        printf("dr: %d\n", dr);
                                        *(outputByte) = *(outputByte) | dr;
                                        byte += (unsigned int)keyLength - offset;
                            
                                        if(byte == 8){
                                            byte = 0;
                                            printf("output byte: %d\n", *(outputByte));
                                            fwrite(outputByte, 1, 1, out_file);
                                            *(outputByte) = 0;
                                            int newOffset = 8 - offset;
                                            if(offset > 8 ){printf("sfsafdfdsfsadfssfsdfdssdsfdsfdsfadsfasdfasdfsafasfadasfdadsfa\n");}
                                            unsigned char dl = d << newOffset;
                                            *(outputByte) = *(outputByte) | dl;
                                            printf("output byte: %d\n", *(outputByte));
                                            fwrite(outputByte, 1, 1, out_file);
                                            byte += offset;
                                         }
                                    }else{
                                        dl = d << offset;
                                        *(outputByte) = *(outputByte) | dl;
                                        byte += keyLength;
                                        printf("output byte: %d\n", *(outputByte));
                                        fwrite(outputByte, 1, 1, out_file);
                                    }
                                }
                            }else{
                                if(nodeCount == power2(keyLength) + 1){
                                    keyLength++;
                                    printf("keyLength2: %d\n", keyLength);
                                } 
                            }
                        }
                    }else{

                        insertAtEnd(nodeCount, temp, tempCodeLength, keyLength);
                        int offset = 8 - keyLength - byte;
                        unsigned char dl = d << offset;
                        printf("dl: %d\n", dl);
                        *(outputByte) = *(outputByte) | dl;
                        byte += keyLength;
                        *(string) = *(base);
                        stringCodeLength = 2;
                        if(x == 0){
                            printf("the finale outputtttttttttttttttttt\n");
                            if(nodeCount == power2(keyLength) + 1){
                                keyLength++;
                                printf("keyLength3: %d\n", keyLength);
        
                            }
                            outputData = output(*(string), stringCodeLength);
                            if(outputData == NULL){
                                printf("not found\n");
                            }
                            dkeyLength = outputData->keyLength;
                            d = (unsigned char)outputData->key; //code that we are about to output
                            printf("d: %d\n", d);
                            
                            printf("byte: %d\n", byte);
                            offset = 8 - keyLength - byte;
                            
                            if(offset < 0){
                                offset = -offset;
                                unsigned char dr = d >> offset;
                                printf("dr: %d\n", dr);
                                *(outputByte) = *(outputByte) | dr;
                                byte += (unsigned int)keyLength - offset;
                            
                                if(byte == 8){
                                    byte = 0;
                                    printf("output byte: %d\n", *(outputByte));
                                    fwrite(outputByte, 1, 1, out_file);
                                    *(outputByte) = 0;
                                    int newOffset = 8 - offset;
                                    if(offset > 8 ){printf("sfsafdfdsfsadfssfsdfdssddfasdfasdfasdfadsfasfasdfasdf\n");}
                                    unsigned char dl = d << newOffset;
                                    *(outputByte) = *(outputByte) | dl;
                                    printf("output byte: %d\n", *(outputByte));
                                    fwrite(outputByte, 1, 1, out_file);
                                    byte += offset;
                                }
                            }else{
                            
                                dl = d << offset;
                                *(outputByte) = *(outputByte) | dl;
                                byte += keyLength;
                                printf("output byte: %d\n", *(outputByte));
                                fwrite(outputByte, 1, 1, out_file);
                            }
                        }else{
                            if(nodeCount == power2(keyLength) + 1){
                                keyLength++;
                                printf("keyLength4: %d\n", keyLength);
                                printf("nodeCount: %d\n", nodeCount);
                            }
                        }
                        
                    }
                
                }
            }
            counter = 1;
        }

    }
    if(x){
        printf("Invalid encoder input: %d %d %d %d \n", *(littleEndianSize), *(littleEndianSize + 1), *(littleEndianSize + 2), *(littleEndianSize + 3), *(data));
    }
    if(!counter){
        printf("Invalid encoder input: %d %d %d %d \n", *(littleEndianSize), *(littleEndianSize + 1), *(littleEndianSize + 2), *(littleEndianSize + 3));
    }
    struct node* temp = head;
    struct node* temp2;
    nodeCount = 0;
    keyLength = 3;
    free(littleEndianSize);
    free(size);
    free(data);
    free(string);
    free(base);
    free(outputByte);
    free(outputPadding);
    while(temp){
        //you can free head and end becuase a new table is created with a new head and end
        temp2 = temp;
        temp = temp -> next;
        free(temp2);
    }

}
