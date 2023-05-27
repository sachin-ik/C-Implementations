#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* next;
};

typedef struct node node;

void printList(node* head)
{
    node* temp = head;
    while(temp != NULL)
    {
        printf("%d->",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void addNode(node* head, int data)
{
    node *newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;
    node* temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void removeNode(node* head, int data)
{
    node* temp = head;
    while(temp->next != NULL)
    {
        if(temp->next->data == data)
        {
            node* temp1 = temp->next;
            temp->next = temp->next->next;
            free(temp1);
            return;
        }
        temp = temp->next;
    }
}

node* reverseList(node* head)
{
    node* prev = NULL;
    node* current = head;
    node* temp;
    // a->b->c->d->null
    // null<-a<-b<-c<-d
    while(current != NULL)
    {
        temp = current;
        current = current->next;
        temp->next = prev;
        prev = temp;
    }
    return temp;
}

void deleteNode(node* rmNode)
{
    if(rmNode == NULL) return;
    node* temp = rmNode->next;
    if(temp == NULL){
        printf("Cannot delete last node\n");
        return;
    }
    rmNode->data = temp->data;
    rmNode->next = temp->next;
    free(temp);
}


//function to find middle of a linked list
node* findMiddle(node* head)
{
    node* slow = head;
    node* fast = head;
    while(fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//function to find nth node from the end of a linked list
node* findNthFromEnd(node* head, int n)
{
    node* slow = head;
    node* fast = head;
    int i;
    //find the nth node from the beginning
    for(i=0;i<n;i++)
    {
        if(fast == NULL) return NULL;
        fast = fast->next;
    }
    //move both pointers till the end
    //slow pointer will be at the nth node from the end
    while(fast != NULL)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

//function to find nth node from the beginning of a linked list
node* findNthFromBeginning(node* head, int n)
{
    if(n==0) return NULL;
    node* temp = head;
    int i;
    for(i=1;i<n;i++)
    {
        if(temp == NULL) return NULL;
        temp = temp->next;
    }
    return temp;
}


int main()
{
    node* head = (node*)malloc(sizeof(node));
    head->data = 1;
    head->next = NULL;
    addNode(head, 2);
    addNode(head, 3);
    addNode(head, 4);
    printList(head);
    deleteNode(head->next->next->next);//delete node with node as input
    head = reverseList(head);
    printList(head);

    node* middle = findMiddle(head);
    printf("Middle of the list is %d\n",middle->data);
    
    node* nthFromEnd = findNthFromEnd(head, 2);
    printf("2nd node from the end is %d\n",nthFromEnd->data);

    node* nthFromBeginning = findNthFromBeginning(head, 2);
    printf("2nd node from the beginning is %d\n",nthFromBeginning->data);

    return 0;
}