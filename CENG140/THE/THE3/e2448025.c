#include <stdio.h>
#include <stdlib.h>
#include "the3.h"

Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth){
    int i;
    Apartment *new_apart=(Apartment*)malloc(sizeof(Apartment));
    Apartment *curr=head;
    new_apart->name=apartment_name;
    new_apart->max_bandwidth= max_bandwidth;
    new_apart->flat_list= NULL;
    if(head==NULL){
        new_apart->next=new_apart; 
        return new_apart;
    }
    if(index==0){
        while(curr->next!=head){curr=curr->next;}
        curr->next=new_apart;
        new_apart->next=head;
        return new_apart;
    }
    else{
        for(i=1;i<index;i++){curr=curr->next;}
        new_apart->next=curr->next;
        curr->next=new_apart;
        return head;
    }    
}

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth){
    int band=0,max,i;
    Flat *new_flat=(Flat*)malloc(sizeof(Flat));
    Flat *temp,*temp1;
    Apartment *curr=head;    
    new_flat->id= flat_id;
    new_flat->is_empty= 0;
    while(*(curr->name)!= *(apartment_name)){curr=curr->next;}
    temp=curr->flat_list;
    max=curr->max_bandwidth;
    while(temp!= NULL){band+=(temp->initial_bandwidth);temp=temp->next;}
    if(band+initial_bandwidth<=max){new_flat->initial_bandwidth=initial_bandwidth;}
    else{new_flat->initial_bandwidth=(max-band);}
    temp1=curr->flat_list;
    for(i=0;i<index;i++){temp1=temp1->next;}
    if(index==0){
        new_flat->prev=NULL;
        temp1->prev=new_flat;
        new_flat->next=temp1;
        curr->flat_list=new_flat;
    }
    else{
        new_flat->next= temp1;
        new_flat->prev= temp1->prev;
        temp1->prev->next=new_flat;
        temp1->prev=new_flat;        
    }
}

Apartment* remove_apartment(Apartment* head, char* apartment_name){
    Apartment *curr=head,*temp=head;
    Flat *temp_flat, *curr_flat;
    if(head->next==head || head ==NULL){return NULL;}
    while(temp->next!=head){temp=temp->next;}    
    while(*(curr->name)!=*(apartment_name)){temp=curr;curr=curr->next;}
    temp->next=curr->next;
    if(curr!=head){
        curr_flat= curr->flat_list;
        while(curr_flat){
            temp_flat=curr_flat;
            curr_flat=curr_flat->next;
            free(temp_flat);
        }
        free(curr);        
    }
    else if(curr==head){
        head=curr->next;
        curr_flat= curr->flat_list;
        while(curr_flat){
            temp_flat=curr_flat;
            curr_flat=curr_flat->next;
            free(temp_flat);
        }
        free(curr);
    }
    return head;
}

void make_flat_empty(Apartment* head, char* apartment_name, int flat_id){
    Apartment *curr=head;
    Flat *temp;
    while(*(curr->name)!=*(apartment_name)){curr=curr->next;}
    temp=curr->flat_list;
    while(temp->id!=flat_id){temp=temp->next;}
    temp->is_empty=1;
    temp->initial_bandwidth=0;
}

int find_sum_of_max_bandwidths(Apartment* head){
    int sum=0;
    Apartment *curr=head;
    if(head==NULL){return sum;}
    if(curr->next==head){sum+= curr->max_bandwidth; return sum;}
    else{
        sum += curr->max_bandwidth;
        curr= curr->next;
        while(curr!= head){sum+= curr->max_bandwidth; curr=curr->next;}
        return sum;
    }
}

Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2){
    Apartment *apt1=head, *apt2=head, *apt2_prev=head;
    Flat *flat1, *flat2;
    while(*(apt1->name)!= *(apartment_name_1)){apt1=apt1->next;}
    while(apt2_prev->next != head){apt2_prev= apt2_prev->next;}
    while(*(apt2->name)!= *(apartment_name_2)){apt2_prev=apt2; apt2=apt2->next;}
    apt1->max_bandwidth += apt2->max_bandwidth;
    flat1 = apt1->flat_list;
    flat2 = apt2->flat_list;    
    if(flat1==NULL){apt1->flat_list=flat2;}
    else{
        while(flat1->next != NULL){flat1 =flat1->next;}
        flat1->next=flat2;
        if(flat2!=NULL){flat2->prev=flat1;}               
    }
    if(apt2==head){
        apt2_prev->next= apt2->next;
        head=apt2->next;
        free(apt2);
    }
    else{
        apt2_prev->next=apt2->next;
        free(apt2);
    } 
    return head;
}

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list){
    int i;
    Apartment *apt=head, *curr_apt;
    Flat *new_flat, *curr_flat;    
    while(*(apt->name) != *(new_apartment_name)){apt=apt->next;}
    new_flat= apt->flat_list;
    while(new_flat->id !=flat_id_to_shift){new_flat=new_flat->next;}
    for(i=0; flat_id_list[i] != 0; i++){
        curr_apt=head;
        while(curr_apt){
            curr_flat= curr_apt->flat_list;
            if(curr_flat == NULL){                 
                curr_apt= curr_apt->next; 
                continue;
            }            
            while (curr_flat != NULL){
                if(curr_flat->id == flat_id_list[i]){
                    break;
                }
                curr_flat = curr_flat->next;
            }
            if(curr_flat == NULL){
                curr_apt= curr_apt->next; 
                continue;
            }
            else if(curr_flat->id == flat_id_list[i]){
                break;
            }                                       
        }      
        if(curr_flat->prev == NULL){
            if(curr_flat->next== NULL){
                curr_apt->flat_list= NULL;
            }
            else{
                curr_flat->next->prev= NULL;
                curr_apt->flat_list= curr_flat->next;  
            }                      
            if(new_flat->prev==NULL){
                curr_flat->next= new_flat;
                new_flat->prev= curr_flat;
                apt->flat_list= curr_flat;
            }
            else{
                new_flat->prev->next = curr_flat;
                curr_flat->prev = new_flat->prev;
                new_flat->prev = curr_flat;
                curr_flat->next = new_flat;
            }       
        }
        else{
            if(curr_flat->next == NULL){
                curr_flat->prev->next= NULL;
            }
            else{
                curr_flat->prev->next = curr_flat->next;
                curr_flat->next->prev = curr_flat->prev;
            }            
            if(new_flat->prev==NULL){
                curr_flat->prev= NULL;
                curr_flat->next= new_flat;
                new_flat->prev= curr_flat;
                apt->flat_list= curr_flat;
            }
            else{
                new_flat->prev->next = curr_flat;
                curr_flat->prev = new_flat->prev;
                new_flat->prev = curr_flat;
                curr_flat->next = new_flat;
            }   
        }
        curr_apt ->max_bandwidth -= curr_flat->initial_bandwidth;
        apt->max_bandwidth += curr_flat-> initial_bandwidth;        
    }    
}