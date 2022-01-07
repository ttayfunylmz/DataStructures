#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10
#define EMPTY -1

#define TRUE 1
#define FALSE 0

typedef int BOOL;
//LIFO -> Last in First Out
typedef struct tagStack {
    int* pData; //For pData part of the Stack Abstract Data Type
    int size; //Size of the data
    int sp; //The indicator for the new entries and removal (Stack Pointer)
}STACK;

STACK* CreateStack(int size);
void DestroyStack(STACK* pStack);

BOOL Push(STACK* pStack, int data);
BOOL IsFull(STACK* pStack);

BOOL Pop(STACK* pStack, int* pData);
BOOL Peek(STACK* pStack, int* pData);
BOOL IsEmpty(STACK* pStack);

//Instead of creating a new box in every case, we are making it in a function.
STACK* CreateStack(int size) {
    STACK* pStack = NULL;

    pStack = (STACK*)malloc(sizeof(STACK));
    if(NULL == pStack) {
        fprintf(stderr, "Can NOT allocate memory for the STACK structure");
        exit(EXIT_FAILURE);
    }
    pStack->pData = (int*)malloc(sizeof(int) * size);
    if(NULL == pStack->pData) {
        fprintf(stderr, "Can NOT allocate memory for the STACK DATA");
        exit(EXIT_FAILURE);
    }
    pStack->size = size;
    //Applying second assumption :
    pStack->sp = EMPTY; //SP points first data top REMOVE (-1)

    return pStack;
}

//By that function, we free our data which means we are destroying them from the memory.
void DestroyStack(STACK* pStack) {
    if(NULL != pStack) {
        free(pStack->pData);
        free(pStack);
    }
    else {
        printf("Your pStack is already CLEANED-UP!");
        exit(EXIT_FAILURE);
    }
}

//To add data to our Stack, we must use our Push function.
BOOL Push(STACK* pStack, int data) {
    if(NULL != pStack) {
        if(TRUE == IsFull(pStack)) {
            printf("You can NOT push more. Stack is FULL. STACK OVERFLOW.");
            return FALSE;
        }
        //First, we increase the sp and then we assign a value to the data. Because we are adding data.
        pStack->sp++;
        pStack->pData[pStack->sp] = data;
        return TRUE;
    }
    return FALSE;
}

BOOL IsFull(STACK* pStack) {
    //We used TERNARY OPERATOR to make sure the capacity is FULL.
    return (pStack->sp == pStack->size) ? TRUE : FALSE;
}

//To remove data from our Stack, we must use our Pop function.
BOOL Pop(STACK* pStack, int* pData) {
    if(NULL != pStack) {
        if(TRUE == IsEmpty(pStack)) {
            printf("You can NOT pull. Stack is EMPTY. STACK UNDERFLOW.");
            return FALSE;
        }
        //First, we assign a value in the data and then we decrease it. Because we are removing data.
        *pData = pStack->pData[pStack->sp];
        pStack->sp--;
        return TRUE;
    }
    return FALSE;
}

//We are not adding or removing data in Peek function. It only shows the PEEK DATA.
BOOL Peek(STACK* pStack, int* pData) {
    if(NULL != pStack) {
        if(TRUE == IsEmpty(pStack)) {
            printf("You can NOT pull. Stack is EMPTY. STACK UNDERFLOW.");
            return FALSE;
        }
        *pData = pStack->pData[pStack->sp];
        return TRUE;
    }
    return FALSE;
}
//We used TERNARY OPERATOR to make our Stack is empty.
BOOL IsEmpty(STACK* pStack) {
    return (pStack->sp == EMPTY) ? TRUE : FALSE;
}

int main() {
    STACK* pStack1;
    int i, data;

    pStack1 = CreateStack(STACK_SIZE); //We defined STACK_SIZE as 10.

    for(i=0; i<STACK_SIZE; ++i){
        printf("STACK Data : %d\n",i+1);

        if(FALSE == Push(pStack1, i+1))
            printf("Can NOT Push data  %d\n", i+1);
    }
    printf("-----------------------\n");

    if(TRUE == Peek(pStack1, &data))
        printf("PEEKed data from STACK (TOP VALUE) : %d\n", data);
    printf("-----------------------\n");

    for(i=0; i<STACK_SIZE; ++i)
        if(TRUE == Pop(pStack1, &data))
            printf("POPed data from STACK : %d\n", data);

    DestroyStack(pStack1);

    return EXIT_SUCCESS; //This comes from <stdlib.h>
}
