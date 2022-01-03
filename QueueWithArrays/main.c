#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
#define TRUE 1

//Front -> Head
//Read -> Head in reverse
int arr[SIZE], front = -1, rear = -1;

void enQueue(int data); //Just like Push in Stack.
void deQueue(); //Just like Pop in Stack.
void printList();

//We are adding data to the end of the Queue List. So we must increase the rear.
void enQueue(int data) {
    if(rear == SIZE) {
        printf("Queue is full. Queue OVERFLOW.\n");
    }
    else {
        if(front == -1) //This means if we add item for the first time, make the front 0, so we can add items.
            front = 0;
        rear += 1; //Increase the rear.
        arr[rear] = data; //Assign the data to our array's rear index.
    }
}

//We are deleting data from the head of the Queue List. So we must increase the front.
void deQueue() {
    if(front == -1 || front>rear) {
        printf("Queue is empty. Queue UNDERFLOW.\n");
        front = -1; //We must change front and rear to their default versions. So we can use them again.
        rear = -1;
    }
    else {
        front += 1; //Increase the front.
    }
}

void printList() {
    int i;

    for(i = front; i <= rear; ++i) {
        printf("%d ", arr[i]);
    }
}

int main()
{
    int choice;
    while(TRUE) {
        printf("\n1-enQueue");
        printf("\n2-deQueue");
        printf("\nEnter 1 for enQueue, 2 for deQueue\n");
        scanf("%d", &choice);

        switch(choice) {
        case 1:
            printf("Enter a number to add : ");
            scanf("%d", &choice);
            enQueue(choice);
            printList();
            break;
        case 2:
            deQueue();
            printList();
            break;
        default:
            printf("Enter a valid number !");
            break;
        }
    }
    return 0;
}
