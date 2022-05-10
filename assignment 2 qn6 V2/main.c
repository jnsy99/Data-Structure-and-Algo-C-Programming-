#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}


int numMountainPairs(CDblLinkedList CDLL)
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail


// Write your code here

    CDblListNode *cur = CDLL.head, *nextNode = CDLL.head, *preNode = NULL, *BNode = NULL, *tempNode = NULL;
    int count = CDLL.size, hmin = 0, itemCur = 0, itemNext = 0, itemPre = 0, itemTemp = 0;
    int pairedBool = 0;

    // Special case - If size of list is <=2
    if(CDLL.size <= 2){
        return (count-1);
    }
    cur = cur->pre;

    // Iterate through link list, except last 2 digits to find non-adjacent pairs
    for(int i = 0; i<CDLL.size-2; i++){
        cur = cur->next;
        itemCur = cur->item;
        nextNode = cur->next;
        BNode = cur->next;
        preNode = cur->pre;

        // If current node item is smaller than it's pre & next, skip to next as it will not have any other pairs
        if(itemCur < nextNode->item && itemCur < preNode->item){
            continue;
        }

        // Iterate through the possible partners of current node
        for(int j = 0; j<(CDLL.size-2-i); j++){
            if(i==0 && j==(CDLL.size-3))
                continue;
            // tempNode for traversing nodes between A(cur) and B
            // BNode stores the current partner of cur, to check if they can be pairs
            BNode = BNode->next;
            // hmin stores the smallest node of A(cur) and B
            hmin =  cur->item < BNode->item ? cur->item : BNode->item;
            // pairedBool will be set true(1) after A and B successfully paired
            pairedBool = 0;
            // Check clockwise - check if numbers between A(cur) and B are not bigger than hmin
            if(itemCur >= nextNode->item){
                tempNode = cur->next;
                for(int k = 0; k<=j; k++){
                    if(tempNode->item > hmin){
                        break;
                    }
                    if(k==j){
                        count++;
                        pairedBool = 1;
                        break;
                    }
                    tempNode = tempNode->next;
                }
            }
            // Check Anti-clockwise - check if numbers between A(cur) and B are not bigger than hmin
            if(itemCur >= preNode->item && pairedBool == 0){
                tempNode = cur->pre;
                for(int k = 0; k<(CDLL.size-2-j); k++){
                    if(k+1==CDLL.size-2-j){
                        count++;
                        break;
                    }

                    if(tempNode->item > hmin){
                        break;
                    }

                    tempNode = tempNode->pre;
                }
            }


        }
    }
    return (count);
}
