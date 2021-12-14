#include <stdio.h>
#include <stdlib.h>

#define LIST_LENGTH 10

typedef struct DoublyLinkedList {
    int data;
    struct DoublyLinkedList* next;
    struct DoublyLinkedList* prev;
}DLL;

void PrintListRecursively(DLL* headOfTheList);
DLL* AddItemToEnd(DLL* headOfTheList, int data);
DLL* AddItemToHead(DLL* headOfTheList, int data);
DLL* RemoveItem(DLL* headOfTheList, int toRemove);
DLL* RemoveItemRecursively(DLL* headOfTheList, int toRemove);
DLL* addInOrder(DLL* headOfTheList, int data);



void PrintListRecursively(DLL* headOfTheList) {
    //Base Case
    if(NULL != headOfTheList) {
        printf("Data : %d\n",headOfTheList->data);
        //Progress Towards Base Case
        PrintListRecursively(headOfTheList->next);
    }

}

DLL* AddItemToEnd(DLL* headOfTheList, int data) {
    //Prepare the new item first :
    DLL* newItem = (DLL*)malloc(sizeof(DLL));
    if(NULL == newItem) {
        printf("Can't allocate memory for new item.");
        exit(EXIT_FAILURE); //This one comes from stdlib library.
    }
    newItem->data = data;
    newItem->next = NULL;
    newItem->prev = NULL; //We will set it when we find the correct spot.

    //Case 1 : Empty list :
    if(NULL == headOfTheList)
        return newItem;

    //Case 2 : List contains at least 1 item or more :
    DLL* temp = headOfTheList;

    //Find the last item :
    while(NULL != temp->next)
        temp = temp->next;

    //Set the necessary links appropriately :
    temp->next = newItem;
    newItem->prev = temp; //Don't forget to setting the prev appropriately.

    return headOfTheList;
}

DLL* AddItemToHead(DLL* headOfTheList, int data) {
    //Prepare the new item first :
    DLL* newHead = (DLL*)malloc(sizeof(DLL));
    if(NULL == newHead) {
        printf("Can't allocate memory for new item.");
        exit(EXIT_FAILURE); //This one comes from stdlib library.
    }
    newHead->data = data;
    newHead->prev = NULL; //Because it's gonna be the new first item.

    if(NULL != headOfTheList) {
        headOfTheList->prev = newHead;
        newHead->next = headOfTheList;
        headOfTheList = newHead;
    }else {//If we have an empty list :
        newHead->next = headOfTheList;
    }
    return newHead;
}

DLL* RemoveItem(DLL* headOfTheList, int toRemove) {
    DLL* temp = headOfTheList;

    while(NULL != temp && toRemove != temp->data)
        temp = temp->next;
    //Case 0 : Empty list or list doesn't have "toRemove" (could not be found)
    if(NULL == temp){
        printf("Your list is empty or %d can NOT be FOUND!\n", toRemove);
        return headOfTheList;
    }else { //toRemove FOUND!
        //Case 1 : Remove the first item (first item's prev will be NULL)
        //Case 2 : Remove the last item (last item's next will be NULL)
        //Case 3 : Remove a middle item

        //Delete temp from the list :
        if(NULL != temp->prev)
            temp->prev->next = temp->next; //Setting previous item's next value.
        if(NULL != temp->next)
            temp->next->prev = temp->prev; //Setting next item's prev value.
        //If we would like to remove the head, we must update the head :
        if(temp == headOfTheList)
            headOfTheList = headOfTheList->next;

        free(temp); //For ALL if conditions.
        return headOfTheList;
    }
}


DLL* RemoveItemRecursively(DLL* headOfTheList, int toRemove)
{
    // BASE CASE : HANDLES "Empty list" and "NOT FOUND" cases
    if (NULL != headOfTheList) {
        // FOUND!
        if (toRemove == headOfTheList->data) {
            if (NULL != headOfTheList->next)
                headOfTheList->next->prev = headOfTheList->prev;
            DLL* newHead = headOfTheList->next;
            free(headOfTheList);
            return newHead;
        } else // NOT FOUND!
            // PROGRESS towards the base case
            headOfTheList->next = RemoveItemRecursively(headOfTheList->next, toRemove);
    }
    return headOfTheList;
}

DLL* addInOrder(DLL* headOfTheList, int data) {

    //Case 0 : Empty List :
    if(NULL == headOfTheList){
        headOfTheList = (DLL*)malloc(sizeof(DLL));
        headOfTheList->next = NULL; //Because "headOfTheList" is the only item.
        headOfTheList->prev = NULL;
        headOfTheList->data = data;
        return headOfTheList;
    }
    //Case 1 : New data is smaller than the first data :
    if(headOfTheList->data > data) {
       DLL* temp = (DLL*)malloc(sizeof(DLL));
       temp->data = data;
       temp->next = headOfTheList; //Because "temp" is gonna be the first item of our list.
       headOfTheList->prev = temp; //Connecting the links.
       return temp;
    }
    //Case 2 : New data must be pointed in the middle or last :
    DLL* cur = headOfTheList;
    while(NULL != cur->next && cur->next->data < data)
        cur = cur->next;

    DLL* temp = (DLL*)malloc(sizeof(DLL));
    temp->next = cur->next;
    cur->next = temp;
    temp->prev = cur;

    if(NULL != temp->next)
        temp->next->prev = temp;

    temp->data = data;
    return headOfTheList;

}

int main()
{

    DLL* headOfTheList1 = NULL;
    int i;

    //Trying to remove item from an empty list.
    RemoveItem(headOfTheList1,5);

    printf("--------------------------\n");

    for(i = 0; i < LIST_LENGTH; ++i) {
        headOfTheList1 = AddItemToEnd(headOfTheList1, i+1);
    }
    PrintListRecursively(headOfTheList1);

    printf("--------------------------\n");

    printf("Adding items to head :\n");
    for(i = 10; i<20; ++i) {
        headOfTheList1 = AddItemToHead(headOfTheList1,i+1);
    }
    PrintListRecursively(headOfTheList1);

    printf("--------------------------\n");

    printf("Trying to delete 5 from the list :\n");
    RemoveItem(headOfTheList1,5);
    PrintListRecursively(headOfTheList1);

    printf("--------------------------\n");

    printf("Trying to delete 70 from the list which does NOT EXIST in the list :\n");
    RemoveItem(headOfTheList1,70);

    printf("--------------------------\n");

    DLL* headOfTheList2 = NULL;

    headOfTheList2 = addInOrder(headOfTheList2, 3);
    headOfTheList2 = addInOrder(headOfTheList2, 9);
    headOfTheList2 = addInOrder(headOfTheList2, 1);
    headOfTheList2 = addInOrder(headOfTheList2, 156);
    headOfTheList2 = addInOrder(headOfTheList2, 6);

    PrintListRecursively(headOfTheList2);

    printf("--------------------------\n");

    printf("Removing 9 :\n");
    RemoveItem(headOfTheList2,9);
    PrintListRecursively(headOfTheList2);

    printf("--------------------------\n");

    printf("Removing 32 which does NOT EXIST:\n");
    RemoveItem(headOfTheList2, 32);
    PrintListRecursively(headOfTheList2);

    return 0;
}
