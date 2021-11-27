#include <stdio.h>
#include <stdlib.h> //We are adding this library to use malloc.

//We want to write it like SLLI. So we are declaring it with typedef.
typedef struct SinglyLinkedList {
    int data;
    struct SinglyLinkedList *next;
}SLLI;

int main()
{
    //We can't define them like "struct SLLI*" because we are in the main function.
    //Creating our first node.
    struct SinglyLinkedList* firstNode;

    //Allocating Memory with malloc.
    firstNode = (SLLI*)malloc(sizeof(SLLI));

    //Creating our second node.
    struct SinglyLinkedList* secondNode = (SLLI*)malloc(sizeof(SLLI));

    //Defining our first node's data part.
    firstNode->data = 10;
    firstNode->next = secondNode;

    secondNode->data = 20;
    secondNode->next = NULL; //We want our second node to be the last node. So we declare its next to NULL.

    printf("First Node : %d\nSecond Node : %d",firstNode->data, secondNode->data);



    return 0;
}
