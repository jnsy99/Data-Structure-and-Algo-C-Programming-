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
  int i=0,j=0,k, size,hold;
  char *rev[SIZE];
  char exit[SIZE];
  char temp;
  char x;
  Stack *stack1;
  stack1=malloc(sizeof(Stack));
  //stack1->head = NULL;
  stack1->size = 0;

  if (infix==NULL) return;

  while (infix[j]!='\0') j++;
  size = j;
  for (i=0;i<size;i++){
    rev[i]=infix[--j];
  }
  rev[i] = '\0';

  i=0;
  j=0;
  while(rev[j]!='\0'){
    temp = peek(*stack1);
    hold=0;
    x = rev[j];
    switch((int)x){
      case(32):
        break;
      case(43):

      case(42):

      case(45):

      case(47):
        while((temp=='*'||temp=='/')&& !isEmptyStack(*stack1)&&(int)temp!=41){
            insertNode(inExpLL,temp,OPT);
            pop(stack1);
            }
            push(stack1,x);
            break;
      case(41):
        push(stack1,x);
        break;
      case(40):
        while(temp!=')'){
          if (temp=='*'){
            insertNode(inExpLL,temp,OPT);
          }
          else if (temp=='-'){
            insertNode(inExpLL,temp,OPT);
          }
          else if (temp=='/'){
            insertNode(inExpLL,temp,OPT);
          }
          else if (temp=='+'){
            insertNode(inExpLL,temp,OPT);
          }
          else insertNode(inExpLL,temp,OPERAND);
          pop(stack1);
        }
        pop(stack1);

        break;
      default:
        k=j;
        i=0;
        while ((int)rev[k]>47&&(int)rev[k]<58){
            exit[i++]=rev[k++];
        }
        k=j;
        while ((int)rev[k]>47&&(int)rev[k]<58){
            hold*=10;
            hold+=exit[--i]-'0';
            k++;
        }
        insertNode(inExpLL,hold,OPERAND);
        j=--k;
        break;
    }
    j++;
  }
  while(!isEmptyStack(*stack1)){
    if (temp=='*'){
    insertNode(inExpLL,temp,OPT);}
    if (temp=='-'){
    insertNode(inExpLL,temp,OPT);}
    if (temp=='/'){
    insertNode(inExpLL,temp,OPT);}
    if (temp=='+'){
    insertNode(inExpLL,temp,OPT);
    }
    else insertNode(inExpLL,temp,OPERAND);
    pop(stack1);
    }
  exit[i]=='\0';
}




