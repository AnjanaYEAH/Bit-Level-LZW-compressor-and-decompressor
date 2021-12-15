#include <stdlib.h>
#include <stdio.h>

struct node{
  unsigned long data;
  struct node* next;
  struct node* previous;
};
struct node* head;
struct node* end;

void insertAtEnd(unsigned long a){
    struct node* newn = (struct node*)malloc(sizeof(struct node));
    newn -> data = a;
    newn -> next = end;

    struct node* oneBeforeEnd = end -> previous;
    oneBeforeEnd -> next = newn;
    end -> previous = newn;
}

int main(){
    head = (struct node*)malloc(sizeof(struct node));
    end = (struct node*)malloc(sizeof(struct node));
    head -> next = end;
    head -> data = 0;
    head -> previous = NULL;

    end -> previous = head;
    end -> data = 0;
    end -> next = NULL;

    insertAtEnd(10);
    insertAtEnd(10);
    insertAtEnd(10);
    insertAtEnd(10);
    insertAtEnd(10);
    insertAtEnd(10);
    insertAtEnd(10);
    struct node* temp = head;
    while(temp){
        printf("%ld\n", temp->data);
        temp = temp->next;
    }
}
