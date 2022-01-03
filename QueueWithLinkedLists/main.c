#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 10
#define EMPTY -1

#define TRUE 1
#define FALSE 0

typedef int BOOL;
//FIFO -> First in First out
typedef struct tagQueue {
    int* pData;
    int size;
    int count; //This is like stack pointer (sp)
    int front; //This will show us where to remove the data
    int rear; //This will show us where to add the new data
}QUEUE;

QUEUE* CreateQueue(int size);
void DestroyQueue(QUEUE* pQueue);

BOOL enQueue(QUEUE* pQueue, int data);
BOOL IsFull(QUEUE* pQueue);

BOOL deQueue(QUEUE* pQueue, int* pData);
BOOL Peek(QUEUE* pQueue, int* pData);
BOOL IsEmpty(QUEUE* pQueue);

//Instead of creating a new box in every case, we are making it in a function.
QUEUE* CreateQueue(int size) {
    QUEUE* pQueue = NULL;

    pQueue = (QUEUE*)malloc(sizeof(QUEUE));
    if(NULL == pQueue) {
        fprintf(stderr, "Can NOT allocate memory for QUEUE STRUCTURE\n");
        exit(EXIT_FAILURE);
    }
    pQueue->pData = (int*)malloc(sizeof(int) * size);
    if(NULL == pQueue->pData) {
        fprintf(stderr, "Can NOT allocate memory for QUEUE DATA\n");
    }
    pQueue->size = size;
    pQueue->count = 0;
    pQueue->front = 0;
    pQueue->rear = 0;

    return pQueue;
}

//By that function, we free our data which means we are destroying them from the memory.
void DestroyQueue(QUEUE* pQueue) {
    if(NULL != pQueue) {
        free(pQueue->pData);
        free(pQueue);
    }
}

//This function lets us add the data to the end. (to the REAR)
BOOL enQueue(QUEUE* pQueue, int data) {
    if(NULL != pQueue) { //To check pQueue is Empty.
        if(TRUE == IsFull(pQueue)) {
            printf("Your Queue is already Full. QUEUE OVERFLOW.\n");
            return FALSE;
        }
        pQueue->pData[pQueue->rear] = data; //Assigning the data first (to the rear) and then we are increasing the counter..
        pQueue->count++;
        //Circular Queue update for the Rear.
        pQueue->rear = (pQueue->rear +1) % (pQueue->size);
        return TRUE;
    }
    return FALSE;
}

BOOL IsFull(QUEUE* pQueue) {
    //We used TERNARY OPERATOR to make sure the capacity is FULL.
    return (pQueue->count == pQueue->size) ? TRUE : FALSE;
}

//This function lets us remove the data from the head. (from the FRONT)
BOOL deQueue(QUEUE* pQueue, int* pData) {
    if(NULL != pQueue) { //To check pQueue is Empty.
        if(TRUE == IsEmpty(pQueue)) {
            printf("Your Queue is empty. QUEUE UNDERFLOW.\n");
            return FALSE;
        }
        *pData = pQueue->pData[pQueue->front]; //We are removing data from the front. And then decrease the counter.
        pQueue->count--;
        //Circular Queue update for the Front.
        pQueue->front = (pQueue->front +1) % (pQueue->size);
        return TRUE;
    }
    return FALSE;
}

//Peek function does NOT change anything in the LinkedList. It just traverses the whole list and finds the PEEK spot.
BOOL Peek(QUEUE* pQueue, int* pData) {
    if(NULL != pQueue) {
        if(TRUE == IsEmpty(pQueue)) {
            printf("Your Queue is empty. QUEUE UNDERFLOW.\n");
            return FALSE;
        }
        *pData = pQueue->pData[pQueue->front];
        return TRUE;
    }
    return FALSE;
}

//We used TERNARY OPERATOR to make our Queue is empty.
BOOL IsEmpty(QUEUE* pQueue) {
    return (pQueue->count == EMPTY) ? TRUE : FALSE;
}

int main()
{
    QUEUE* pQueue1;
    int i, data;

    pQueue1 = CreateQueue(QUEUE_SIZE); //We defined QUEUE_SIZE as 10.

    for(i=0; i<QUEUE_SIZE; ++i){
        printf("QUEUE Data : %d\n",i+1);

        if(FALSE == enQueue(pQueue1, i+1))
            printf("Can NOT enQueue data  %d\n", i+1);
    }
    printf("-----------------------\n");

    if(TRUE == Peek(pQueue1, &data))
        printf("PEEKed data from QUEUE (TOP VALUE) : %d\n", data);
    printf("-----------------------\n");

    for(i=0; i<QUEUE_SIZE; ++i)
        if(TRUE == deQueue(pQueue1, &data))
            printf("deQueued data from QUEUE : %d\n", data);

    DestroyQueue(pQueue1);

    return EXIT_SUCCESS;
}
