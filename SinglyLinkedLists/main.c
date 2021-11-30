#include <stdio.h>
#include <stdlib.h>

typedef struct SinglyLinkedList {
    int data;
    struct SinglyLinkedList *next;
}SLLI;

void PrintList(SLLI* headOfTheList); //Function that lets us print the list.
SLLI* AddItemToEnd(SLLI* headOfTheList, int data); //Function that lets us add an item to the end.
SLLI* AddItemToHead(SLLI* headOfTheList, int data); //Function that lets us add an item to the head.
SLLI* DeleteItemFromList(SLLI* headOfTheList, int toDel); //Function that lets us delete an item from anywhere of the list.
SLLI* ReverseList_Iterative(SLLI* headOfTheList); //Function that lets us reverse.


void PrintList(SLLI* headOfTheList)
{
    while (NULL != headOfTheList) {
        printf("Data : %d\n", headOfTheList->data);
        headOfTheList = headOfTheList->next; //Move on to the next one.
    }
}

SLLI* AddItemToEnd(SLLI* headOfTheList, int data)
{
    SLLI* pNewItem; //Declaring a new item to add to the end.

    //Preparing that new item to add.
    pNewItem = (SLLI*)malloc(sizeof(SLLI)); //Allocating memory.
    pNewItem->data = data;
    pNewItem->next = NULL;

    // Case 1 : If list does not exist :
    if (NULL == headOfTheList)
        return pNewItem;
    else {// Case 2 : If case has at least 1 item :
        SLLI* pTemp = headOfTheList; //Declaring a temp because if we use headOfTheList directly, we'd lose our headOfTheList so we'd lose our linked list.
        while (NULL != pTemp->next) //Trying to find the last item of the list.
            pTemp = pTemp->next;
        pTemp->next = pNewItem; //pNewItem is now our last item.
        return  headOfTheList;
    }
}

SLLI* AddItemToHead(SLLI* headOfTheList, int data) {
    SLLI* pNewItem; //Declaring a new item to add to the head.

    //Preparing that new item to add.
    pNewItem = (SLLI*)malloc(sizeof(SLLI)); //Allocating memory.
    pNewItem->data = data;
    pNewItem->next = headOfTheList; //Because we are adding item to the HEAD.
    return pNewItem;
}

SLLI* DeleteItemFromList(SLLI* headOfTheList, int toDel) {
    //Case 0 : Empty List :
    if (NULL != headOfTheList) {
        //If we can get in to that, that means we have list that contains at least 1 item.

        //Case 1 : Remove the first item of the list :
        if (toDel == headOfTheList->data) {
            SLLI* newAddressOfHead = headOfTheList->next; //The 2nd item of the list becomes the head.
            free(headOfTheList); //We don't have a 'garbage collector' in C. So we have to clean it by ourselves.
            return newAddressOfHead; //Returning the new headOfTheList.
        }
        //Case 2&3 : Remove last or the middle item :
        SLLI* prev = NULL;
        SLLI* cur = headOfTheList;
        while(NULL != cur && toDel != cur->data) {
            prev = cur;
            cur = cur->next;
        }
        //Case 4 : NOT FOUND :
        if(NULL != cur) { //If we find that item to delete :
            prev->next = cur->next;
            free(cur);
        }
    }
        else {
            printf("Your list is empty. Add something to your list and TRY AGAIN!\n");
        }
        return headOfTheList;
}

/*SLLI* ReverseList_Iterative(SLLI* headOfTheList){
    SLLI* prev = NULL;
    SLLI* cur = headOfTheList;
    SLLI* next = NULL;

    while(NULL != cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}*/

int main()
{
    SLLI* headOfTheList1 = NULL; //We are declaring that list is empty.

    DeleteItemFromList(headOfTheList1,40); //Must give us an error.

    int i;
    for(i=0; i<10; i++) {
        headOfTheList1 = AddItemToEnd(headOfTheList1, i+1); //We want our data's to be 1-10.
    }

    PrintList(headOfTheList1);

    printf("--------------------------------\n");

    //This loop is gonna add 11 first and 20 last. So our print will be like :
    //20-19-18-17-16-15-14-13-12-11-1-2-3-4-5-6-7-8-9-10
    for(i=10; i<20; i++) {
        headOfTheList1 = AddItemToHead(headOfTheList1, i+1);
    }

    PrintList(headOfTheList1);

    printf("--------------------------------\n");
    printf("Deleting 5 from the list :\n");
    DeleteItemFromList(headOfTheList1,5);
    PrintList(headOfTheList1);

    //printf("--------------------------------\n");

    //ReverseList_Iterative(headOfTheList1);
    //PrintList(headOfTheList1);

    return 0;
}






