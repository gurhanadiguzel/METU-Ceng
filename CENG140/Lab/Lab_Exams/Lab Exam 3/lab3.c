#include "stdio.h"
#include "stdlib.h"
#include "lab3.h"

/* Do not change the lines above */
/* Write your solutions below */

Student** create_student_array_with_teachers(int* student_id_list, int* teacher_id_list, int student_and_teacher_count)
{
    int i;
    Student **arr = (Student**)malloc(sizeof(Student*)*student_and_teacher_count);
    for(i=0;i<student_and_teacher_count;i++){
        arr[i]=(Student*)malloc(sizeof(Student));
        arr[i]->studentID = student_id_list[i];
        arr[i]->best_teacher=(Teacher*)malloc(sizeof(Teacher));
        arr[i]->best_teacher->teacherID = teacher_id_list[i];
    }
    return arr;
}

Node* insert_tail(Node* head, int new_node_data)
{
    Node *newnode, *curr=head;
    newnode=(Node*)malloc(sizeof(Node));
    newnode->data=new_node_data;
    newnode->next= NULL;
    if(head==NULL){
        return newnode;
    }
    else{
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next=newnode;
        return head;
    }
}

Node* remove_kth_node_reversely(Node* head, int index)
{   
    int rev=0, new_index,i;
    Node *curr=head, *temp, *prev;
    while(curr){
        rev+=1;
        curr=curr->next;
    }
    new_index = rev-index-1;
    if(head->next==NULL){
        return NULL;
    }
    else{
        temp=head;
        if(new_index==0){
            head=head->next;
            free(temp);
        }
        else{
            for(i=0;i<new_index;i++){
                prev=temp;
                temp=temp->next;
            }
            prev->next=temp->next;
            free(temp);
        }
    }
    return head;
}

int find_occurrences_of_second_list(Node* head, Node* second_head)
{
    int occ=0;
    Node *curr=head;
    while(curr!=NULL){
        if(curr->data==second_head->data){
            Node *temp=second_head, *temp_curr=curr;
            while(temp){
                if(temp->data==temp_curr->data){
                      temp=temp->next;
                      temp_curr= temp_curr->next;
                }
                else 
                    break;
            }
            if(temp==NULL){
                occ+=1;
            }
        }
        curr=curr->next;
    }
    return occ;
}

Node* cut_and_paste(Node* head, int index_to_cut, int index_to_paste)
{
    int i,j;
    Node *paste=head, *cut=head, *prevc, *prevp;
    for(i=0;i<index_to_cut;i++){
        prevc=cut;
        cut=cut->next;
    }
    for(j=0;j<index_to_paste;j++){
        prevp=paste;
        paste=paste->next;
    }
    if(index_to_paste==index_to_cut){
        return head;
    }
    if(index_to_paste==0){
        prevc->next=cut->next;
        cut->next=head;
        head=cut;
    }
    else{
        prevc->next=cut->next;
        prevp->next=cut;
        cut->next=paste;
    }
    return head;
}

Node* sum_symmetric_pairs(Node* head)
{
    Node *start=(Node*)malloc(sizeof(Node));
    Node *last=head, *temp, *curr=head->next, *A, *S;
    while(last->next!=NULL){last=last->next;}
    start->data= (head->data)+(last->data);
    start->next=NULL;
    S = start;
    temp=last;
    while(curr != temp){
        Node *new_node=(Node*)malloc(sizeof(Node));
        A=head;
        while(A->next!=temp){A=A->next;}
        temp=A;
        new_node->data= curr->data + temp->data;
        new_node->next = NULL;
        start->next=new_node;
        start=new_node;
        curr=curr->next;
    }
    return S;
}