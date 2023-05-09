#include "stdio.h"
#include "stdlib.h"
#include "lab3_copy.h"

/* Do not change the lines above */
/* Write your solutions below */

Student** create_student_array(int* student_id_list, int student_count)
{
    int i;
    Student **array;
    array= (Student**)malloc(sizeof(Student*)*student_count);
    for(i=0;i<student_count;i++){
        array[i]=(Student*)malloc(sizeof(Student));
        array[i]->studentID = student_id_list[i];
    }
    return array;
}

Node* insert_head(Node* head, int new_node_data)
{
    Node *insert=(Node*)malloc(sizeof(Node));
    if(head ==NULL){
        insert -> data = new_node_data;
        insert->next = NULL;
    }
    else{
        insert -> data = new_node_data;
        insert->next = head;
    }
    return insert;
    
}

Node* remove_kth_node(Node* head, int index)
{
    int i;
    Node *curr, *temp;
    if((head->next)==NULL){return NULL;}
    if(index == 0){
        curr = head->next;
        free(head);
        head=curr;
    }
    else{
        curr = head;
        for(i=0;i<index;i++){
            temp=curr;
            curr=curr->next;
        }
        temp->next=curr->next;
        free(curr);
    }
    return head;
}

int find_occurrences(Node* head, int data)
{
    int occ=0;
    Node *curr;
    curr=head;
    if (head==NULL){return 0;}
    while(curr!=NULL){
        if(curr->data==data){
            occ++;
        }
        curr=curr->next;
    }
    return occ;
}

Node* copy_to_head(Node* head, int index)
{
    int i;
    Node *copy, *curr,*A;
    copy= head;
    for(i=0;i<index;i++){
        copy=copy->next;
    }
    curr=(Node*)malloc(sizeof(Node));
    curr->next=NULL;
    A=curr;
    while(copy){
        Node *temp=(Node*)malloc(sizeof(Node));
        temp->data=copy->data;
        temp->next=NULL;
        curr->next=temp;
        curr=temp;
        copy=copy->next;
    }
    curr->next=head;
    return A->next;
}

Node* sum_consecutive_pairs(Node* head)
{      
    Node *sum, *curr;
    sum=(Node*)malloc(sizeof(Node));
    curr=sum;
    while(head->next!=NULL){
        Node *temp=malloc(sizeof(Node));
        temp->data=(head->data)+(head->next->data);
        temp->next=NULL;
        sum->next=temp;
        sum=temp;
        head=head->next;
    }
    return curr->next;
}
