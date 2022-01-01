#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int arr[SIZE], top;

//For adding data, we use PUSH function.
void push(int data) {
    if(top + 1 == SIZE) { //Top starts from -1. So "Top + 1" is the size of the array.
        printf("Stack is full.");
    }
    else { //If stack is not FULL :
        top += 1; //Increasing TOP.
        arr[top] = data; //Defining the data.
    }
}

//For removing data, we use POP function.
void pop() {
    if(top == -1){ //If TOP points -1, this means stack is empty.
        printf("Stack is already empty.");
    }
    else {
        top -= 1; //Decreasing TOP.
    }
}
//Peek function just peeks the data. It does NOT remove it.
int peek() {
    return arr[top]; //Traverses the whole array and shows the TOP.
}

//For printing the list, we use printList function.
void printList() {
    for(int i=0; i<top+1; ++i) {
        printf("%d ", arr[i]);
    }
    printf("==> TOP");
}

int main()
{
    int choice;
    top = -1;

    while(1==1) {
        printf("\n1-Push");
        printf("\n2-Pop");
        printf("\n3-Peek\n");
        printf("Enter 1 for Push, 2 for Pop and 3 for Peek\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter a number to add : ");
                scanf("%d", &choice);
                push(choice);
                printList();
                break;
            case 2:
                pop();
                printList();
                break;
            case 3:
                printf("Top number is : %d", peek());
                break;
            default:
                printf("Enter a valid number!");
                break;
        }
    }
    return 0;
}
