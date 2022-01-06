#include <stdio.h>
#include <stdlib.h>
#define NODE_COUNT 7

typedef struct tagBST {
    int data;
    struct tagBST* left;
    struct tagBST* right;
}NODE;

NODE* addItem(NODE* tree, int data);
void invertTree(NODE* root);
void PrintTree(NODE* root);

NODE* addItem(NODE* tree, int data) {
    //Case 1 : Empty Tree
    if(NULL == tree) {
        NODE* newNode = NULL;
        newNode = (NODE*)malloc(sizeof(NODE));
        if(NULL == newNode) {
            fprintf(stderr, "Can NOT allocate memory for NEW NODE.");
            exit(EXIT_FAILURE);
        }
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        //New node is gonna be the only node. So it will be the root, the leaf and the only item of the tree.
        return newNode;
    }
    else {
        //Case 2 : Tree has at least 1 node
        if(tree->data < data) //If the very new data is bigger then the data in the tree, new data must be located at right.
            tree->right = addItem(tree->right, data);
        else //If the new data is smaller, it must be located at left.
            tree->left = addItem(tree->left, data);
        return tree;
    }
}

void invertTree(NODE* root) {
    if(NULL == root)
        return;
    else {
        NODE* temp = NULL;
        invertTree(root->left);
        invertTree(root->right);

        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

void PrintTree(NODE* root) {
    //BASE CASE
    if(NULL == root)
        return;

    //PROGRESS TOWARDS BASE CASE
    PrintTree(root->left);
    PrintTree(root->right);
    printf("Data : %d\n", root->data);
}

int main() {

    int data[NODE_COUNT] = {4, 2, 6, 1, 5, 3, 7};
    int i;
    NODE* root1 = NULL;

    printf("Normal Tree :\n");
    for(i = 0; i < NODE_COUNT; ++i)
        root1 = addItem(root1, data[i]);

    //Data Must be printed like : 1-2-3-4-5-6-7
    PrintTree(root1);

    printf("------------------------\n");

    printf("Inverted Tree :\n");
    invertTree(root1);
    PrintTree(root1);

    return 0;
}
