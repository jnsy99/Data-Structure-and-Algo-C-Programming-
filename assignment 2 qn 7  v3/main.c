#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}


void in2PreLL(char* infix, LinkedList *inExpLL)
{
    Stack stack1;
    stack1.size = 0;

    char x;


    while(*(int*)infix!= 0 ){
        if(*(int*)infix == 41) // ')'
            *infix = 40;
        else if(*(int*)infix == 40)
            *infix = 41 ;
        infix++;
    }
    infix--;

    // Traverse infix array in reverse order
    while(*(int*)infix!= 0 ){

        // If operand
        if(*(int*)infix >= 0){
                 if( *(int*)infix <= 9)
            while(*(int*)infix >= 0 && *infix <= 9){
                infix--;
            }
            infix++;
            insertNode(inExpLL, atoi(infix), OPERAND);
        }

        // If operator
        else{

            if(*(int*)infix == 41){ //')'
                while(x!=40){
                    if(x!=41)
                        insertNode(inExpLL, x, OPT);
                    pop(&stack1);
                    x = peek(stack1);
                }
             if(stack1.size != 0)
                x = peek(stack1);
                pop(&stack1); //Pop opening braclet
            }
            // if '+' or '-' and stack has equal or higher precedence
            else if(*(int*)infix == 43 && ((int)x == 42 || (int)x == 43|| (int)x == 45 || (int)x == 47)){
                while(x == '*' || x == '/'){
                    insertNode(inExpLL, x, OPT);
                    pop(&stack1);
                    if(stack1.size != 0)
                        x = peek(stack1);
                    else
                        x = '\0';
                }
                push(&stack1,*infix); // Push the new lower precedence operator in
            }

            else if(*(int*)infix == 45 && (((int)x == 42 || (int)x == 43|| (int)x == 45 || (int)x == 47)){
                while(x == '*' || x == '/'){
                    insertNode(inExpLL, x, OPT);
                    pop(&stack1);
                    if(stack1.size != 0)
                        x = peek(stack1);
                    else
                        (int)x = 0;
                }
                push(&stack1,*infix); // Push the new lower precedence operator in
            }




            else{
                push(&stack1,*infix);
            }
        }

        infix--;
    }
    while(stack1.size != 0){
        x = peek(stack1);
        insertNode(inExpLL, x, OPT);
        pop(&stack1);
    }
}
