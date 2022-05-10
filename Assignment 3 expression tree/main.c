#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}

void createExpTree(BTNode** root,char* prefix){
int stop=0;
    *root = malloc(sizeof(BTNode));
    (*root)->left = NULL;
    (*root)->right = NULL;
    if (*root==NULL) return;
    if (prefix[0]=='\0') return;
    while (prefix[0]==' ') strcpy(prefix,prefix+1);




    if (prefix[0]=='*'){
        (*root)->item = prefix[0];
        strcpy(prefix,prefix+1);
        createExpTree(&(*root)->left,prefix);
        if (prefix[0]!='\0'){
            while (prefix[0]==' ')
            strcpy(prefix,prefix+1);
            createExpTree(&(*root)->right,prefix);
        }
    }
        if (prefix[0]=='+'){
        (*root)->item = prefix[0];
        strcpy(prefix,prefix+1);
        createExpTree(&(*root)->left,prefix);
        if (prefix[0]!='\0'){
            while (prefix[0]==' ') strcpy(prefix,prefix+1);
            createExpTree(&(*root)->right,prefix);
        }
    }
    if (prefix[0]=='-'){
        (*root)->item = prefix[0];
        strcpy(prefix,prefix+1);
        createExpTree(&(*root)->left,prefix);
        if (prefix[0]!='\0'){
            while (prefix[0]==' ') strcpy(prefix,prefix+1);
            createExpTree(&(*root)->right,prefix);
        }
    }
    if (prefix[0]=='/'){
        (*root)->item = prefix[0];
        strcpy(prefix,prefix+1);
        createExpTree(&(*root)->left,prefix);
        if (prefix[0]!='\0'){
            while (prefix[0]==' ') strcpy(prefix,prefix+1);
            createExpTree(&(*root)->right,prefix);
        }
    }


    else{
        while ((int)prefix[0]>47&&(int)prefix[0]<58){
            stop*=10;
            stop+=prefix[0]-'0';
            strcpy(prefix,prefix+1);
        }
        (*root)->item = stop;
        return;
    }


}

void printTree(BTNode *node){
    printTree(node->left);
    if (node->item=='/'){
        printf("%c ", node->item);}
    if (node->item=='*'){
        printf("%c ", node->item);}
    if (node->item=='+'){
        printf("%c ", node->item);}
    if (node->item=='-'){
        printf("%c ", node->item);}
    if (node==0)
        return;
    //printTree(node->left);
    else printf("%d ", node->item);{
        printTree(node->right);}

    return;
}


void printTreePostfix(BTNode *node){
   //Write your code here
    if (node==NULL)
        return;
   printTreePostfix(node->right);
   printTreePostfix(node->left);
   //printTreePostfix(node->right);
    if (node->item=='/'){
        printf("%c ", node->item);}
    if (node->item=='*'){
        printf("%c ", node->item);}
    if (node->item=='+'){
        printf("%c ", node->item);}
    if (node->item=='-'){
        printf("%c ", node->item);}
   else printf("%d ", node->item);{
   return;}
}

double computeTree(BTNode *node){
    double l,r;

    if (node==NULL) return 0;
    if (node->left == NULL && node->right == NULL) return node->item;

    l = computeTree(node->left);
    r = computeTree(node->right);

    switch(node->item){
        case('+'):
            return l+r;
        case('-'):
            return l-r;
        case('*'):
            return l*r;
        case('/'):
            return l/r;
    }
}
