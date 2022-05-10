#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	reverseKNodes(&head, K);
	printList(head);
    deleteList(&head);
	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
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

void reverseKNodes(ListNode** head, int K){

    ListNode *cur;
    ListNode *temp,*prev,*next;
    ListNode *temp1start,*temp1end,*temp2start,*temp2end,*temprearstart,*temprearend, *penis;
    //ListNode *
    cur = *head;
    prev=*head;
    next=NULL;
    int size=0,cnt=0;
    int numofsets;
    int i,j,m,x;
    if (K==0){
        return;
    }

    while (cur!= NULL) {
        if(size==K-1){
            temp=cur;
        }
        size++;
        cur=cur->next;
        //prev=cur;
	}

    if(size==0 ||size<K){
        return;
    }
    cur = *head;
        if(size==K){
            penis = cur;
            while(cur!=NULL){
                next = cur->next;  //increment by 1
                cur->next = prev;  //reversing
                prev = cur;        //increment by 1
                cur = next;        //increment by 1
            }
            penis->next=NULL;
            *head=prev;
            return;
        }
        //*head=temp;
        numofsets =(size/K)*0.5;
        printf("size %d\n",size);
        printf("nos %d\n",numofsets);



            for(i=0;i<numofsets;i++){
                temp1end=cur;
                //printf("b%d",cur->item);
                for(j=0;j<K;j++){
                    next = cur->next;  //increment by 1
                    cur->next = prev;  //reversing
                    prev = cur;        //increment by 1
                    cur = next;        //increment by 1
                  //  printf("c%d",cur->item);
                }
                temp1start=prev;
                if (i!=0) temp2end->next = temp1start;
                temp2end=cur;
                for(m=0;m<K;m++){
                    next = cur->next;  //increment by 1
                    cur->next = prev;  //reversing
                    prev = cur;        //increment by 1
                    cur = next;        //increment by 1
                          //  printf("f%d",cur->item);
                }

                temp2start = prev;
                temp1end->next = temp2start;
                      //  printf("g%d",temp1end->item);
                    //printf("gkk%d",temp2start->item);
            }
            //printf("wns %d",size-(numofsets*2*K));
            if(size-(numofsets*2*K)>=K){
                temprearend = cur;
                 for(x=0;x<K;x++){
                    next = cur->next;  //increment by 1
                    cur->next = prev;  //reversing
                    prev = cur;        //increment by 1
                    cur = next;        //increment by 1
                         //   printf("h%d",cur->item);
                }
                temprearstart=prev;
                temp2end->next = temprearstart;

                temprearend->next = cur;
                //printf("kl%d",temp2end->item);
               // printf("lol%d",temprearstart->item);
                       // printf("i%d",cur->item);
            }
            else
                temp2end->next= cur;

                       // printf("j%d",cur->item);


            *head = temp;

            return;


}
