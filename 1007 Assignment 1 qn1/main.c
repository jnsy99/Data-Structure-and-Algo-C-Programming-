#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}

		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

ListNode *reverseSegment(ListNode* head, int start, int end)
{

    int i=0,size=0; //size=0;
    ListNode *cur,*tempstart,*prev,*next, *tempend, *reversestart, *reverseend;

    cur = head;
    while(cur!=NULL){
        size++;
        cur=cur->next;
    }

    prev = head;
    cur = head;
    next= cur->next;
    for (i=0;i<start-1;i++){
        cur = next;//traverse
        next=cur->next; //traverse
    }
    tempstart = cur;
    cur=head;
    next=cur->next;
    for(i=0;i<end+1;i++){
        cur = next;
        next = cur->next;

    }
    tempend=cur;
    cur=head;
    next=cur->next;
    for(i=0;i<start;i++){
        cur = next;
        next = cur->next;
    }
    reversestart=cur;
    prev = cur;
    for(i=0;i<end-start+1;i++){
        next = cur->next;  //increment by 1
        cur->next = prev;  //reversing
        prev = cur;        //increment by 1
        cur = next;        //increment by 1
    }
    reverseend=prev;
    tempstart->next=reverseend;
    reversestart->next=tempend;

    if(end==size){
        reverseend->next=NULL;
    }

    if(start==0){
        return reverseend;
    }
    else
        return head;
}

    /*prev = NULL
    cur = head
    next = cur->next
    if (head==NULL){  // for the first head pointer
        head = temp=next;
    }
    else{



    for(i=0;i<=end;i++){
        //while(current!=NULL){
           // next=current->next;
            //current->next= prev;
            //temp->next = prev; //taking the link part of current node as the prev node

            //prev = current;
           // current = next;
            prev = current;
            current = next;
            current-> next = prev;
            next = next->next;

        }
    head = prev;
    return head;
    }*/

