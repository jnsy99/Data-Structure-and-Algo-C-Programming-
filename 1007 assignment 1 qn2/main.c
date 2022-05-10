#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

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


	triPartition(&head, pivot);
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

void triPartition(ListNode** head, int pivot){
        ListNode *prev = NULL, *cur, *next;
  ListNode* lessStart=NULL,*lessEnd=NULL,*midStart=NULL,*midEnd=NULL,*moreStart=NULL,*moreEnd=NULL;
  cur=*head;
  int size = 0;

        while(cur!=NULL){
            size++;
            cur = cur->next;
        }
        if(size==0 || size==1){
            return;
        }
        cur = *head;

        while (cur!=NULL){
            if(cur->item==pivot){
                if(midStart==NULL){
                    midStart = cur;
                    midEnd = cur;

                }
                else{
                midEnd->next = cur;
                midEnd = cur;

                }
            }
            else if(cur->item < pivot){
                if(lessStart==NULL){
                    lessStart = cur;
                    lessEnd = cur;

                }
                else{
                lessEnd->next = cur;
                lessEnd = cur;

                }
            }
            else if(cur->item > pivot) {
                if(moreStart==NULL){
                    moreStart = cur;
                    moreEnd = cur;

                }
                else{
                moreEnd->next = cur;
                moreEnd = cur;

                }
            }
            cur = cur->next;
        }
		if (lessStart==NULL||lessEnd==NULL||midStart==NULL||midEnd==NULL||moreStart==NULL||moreEnd==NULL){
			return;
		}

		lessEnd ->next = midStart;
		midEnd->next = moreStart;
		moreEnd->next = NULL;
		*head=lessStart;
		if(lessStart==NULL){
            if (midStart==NULL){
               *head=moreStart;
               return;
            }
            *head=midStart;
            return;
		}

		if (midStart==NULL){
            if (lessStart==NULL){
                *head=moreStart;
                return;
            }
            else if (moreStart==NULL){
                lessEnd
                *head=lessStart;
                return;
            }
            else {
                lessEnd->next = moreStart;
                *head= lessStart;
            }
		}

		if (moreStart==NULL){
            if (lessStart==NULL){
                *head = midStart;
                return;
            }
            else if (midStart==NULL){
                *head = lessStart;
                return;
            }
		}
}
		/*if (midStart==NULL){
			lessEnd->next = moreStart;
		}
        else lessEnd->next= midStart;

        if (lessStart==NULL){
			if (midStart==NULL){
				*head = moreStart;
			}
			else *head = midStart;
			return;
		}

		if(moreStart==NULL){
			midEnd->next = NULL;
		}
		else midEnd->next = moreStart;
        moreEnd->next = NULL;
		*head=lessStart;*/






   /* while(cur!=NULL){
        if((*head)->item==pivot){
            if(tempmidStart==NULL)
                tempmidStart=tempmidEnd= head;
            else{
                tempmidEnd->next=head;
                tempmidEnd=tempmidEnd->next;
            }
        }
        else if((*head)->item<pivot){
            if (templessStart ==NULL)
            {   templessEnd=head;
                templessStart= *head;
                templessEnd=templessStart;
            }
            else {
                templessEnd->next=head;

                templessEnd->head;
            }

        }
        else {
            if(tempmoreStart==NULL){
                tempmoreEnd=head;
                tempmoreEndStart= head;
                tempmoreEnd= templessStart;
            }
            else {
                tempmoreEnd->next=head;
                tempmoreend=head;
            }

        }
        head= head->next;
    }
    if (templessStart==NULL){
        if(tempmidStart==NULL){
            return tempmoreStart
        }
        tempmidEnd->next = tempmoreStart;
        return tempmidStart;
    }
    if(tempmoreEnd!=NULL){
        tempmoreEnd->next = NULL;
    }
    if (tempmidStart==NULL){
        templessEnd->next= tempmidStart;
        tempmidEnd->next=tempmoreStart;
        return templessStart;

    }
*/
//}
