#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    this->head = NULL;
    this->size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */    
    this->head = NULL;
    this->size = 0;
    Node<T> *curr = obj.getFirstNode();
    for(int i =0;i<obj.getSize();i++){
            insertAtTheEnd(curr->data);
            curr = curr->next;
    } 
   
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    Node<T>* curr= head;
    for(int i=0 ; i<size; i++){
        if(head == head->next){
            delete  head;
            this->head = NULL;
            this->size = 0; 
        }
        else{
            head->prev->next = head->next;
            head->next -> prev= head->prev; 
            head = head->next;         
            delete  curr ;
            curr=head;
        }               
    }    
}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    return this->size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    if(head == NULL){return true;}
    else{return false;}
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    if(head == NULL){
        return false;
    }
    Node<T> *curr= head;
    for(int i=0; i<size; i++){
        if(curr == node){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
    if(head == NULL){ return NULL;}
    else { return this->head;}
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    if(head == NULL){ return NULL;}
    else { return this->head->prev;}
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    Node<T> *temp = head;    
    for(int i=0; i<size; i++){
        if(temp->data == data){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
    Node<T> *temp = head;  
    if(index >= size || index <0) {
        return NULL;
    }
    for(int i=0; i<index ; i++){         
        temp = temp->next;
    }
    return temp;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */     
    if(head==NULL){
        this->head = new Node<T>(data);
        this->head->next = head;
        this->head->prev = head;       
    }
    else{
        Node<T>* curr = head;
        Node<T>* new_node = new Node<T>(data,curr->prev, curr);
        curr -> prev -> next = new_node;
        curr -> prev = new_node;
        head = new_node;
    } 
    this->size ++;    
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */      
    if(head == NULL){
        this->head = new Node<T>(data);
        this->head->next = head;
        this->head->prev = head;
    }
    else{ 
        Node<T>* curr = head;
        Node<T>* new_node = new Node<T>(data,head -> prev,head);             
        curr -> prev -> next = new_node;
        curr -> prev = new_node;        
    }
    this->size ++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    Node<T> *curr = head;
    if(contains(node)){
        for(int i=0;i<size;i++){        
            if(curr == node){
                Node<T>* new_node = new Node<T>(data);
                new_node -> next = curr -> next;
                new_node -> prev = curr;
                curr -> next -> prev = new_node;
                curr -> next = new_node;
                size ++;
            }
        curr = curr->next;
        } 
    }       
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
    if(k>=2){
        Node<T> *curr= head;        
        int n = 1;
        for(int i=0; i<size;i++){           
            if(n+1==k){
                Node<T>* new_node = new Node<T>(data);
                new_node->next = curr->next;
                new_node->prev = curr;
                curr->next->prev = new_node;
                curr->next = new_node;
                curr = curr->next;
                size ++; 
                n=0;                        
            }
            else{
                curr = curr->next;
                n ++;
            } 
                               
        }
    }    
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    Node<T>* curr= head;
    if (head != NULL && contains(node)){
        if (node == head){
            if(size ==1){
                delete head;
                head =NULL;
            }
            else{
                head->prev->next = head->next;
                head->next ->prev = head->prev;
                head = curr->next;
                delete curr;
            }            
            size --;
        }
        else{
            for(int i=0; i<size; i++){
                if(curr->next == node){
                    curr ->next = curr ->next->next;
                    curr ->next ->prev = curr;
                    delete node;
                    size --;
                    break;
                }
            curr = curr->next;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
    Node<T>* curr= head;
    Node<T>* temp;
    if(head != NULL){       
        for(int i=0; i<size; i++){
            if(size ==1 && head->data ==data){
                delete curr;
                head = NULL;
                size = 0;
                break;
            } 
            if(head->data ==data){
                head->prev->next = head->next;
                head->next->prev = head->prev;
                head = head->next;
                delete curr;
                curr = head;
                size --;
                i--;
                continue;          
            }
            else if(curr->next->data == data){
                temp = curr->next;
                curr->next = curr->next ->next;
                curr->next->prev = curr;
                delete temp;
                i--;
                size --;
            }
            curr = curr->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    Node<T>* curr= head;
    for(int i=0 ; i<size; i++){
        if(head == head->next){
            delete head;
            head = NULL;
            size = 0; 
        }
        else{
            head->prev->next = head->next;
            head->next -> prev= head->prev; 
            head = head->next;         
            delete curr;
            curr=head;
        }               
    }    
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    if(k>=2){
        Node<T>* curr= head;
        Node<T>* temp;
        int n = 2;
        int s = size;
        for(int i=0; i<s; i++){
            if(n%k == 0 && curr->next != head){
                temp = curr->next;
                curr->next = curr->next->next;
                curr->next->prev =curr;
                delete temp;
                curr = curr->next;
                i++;
                size--;
                n=2;
            }
            else{
                curr = curr->next;
                n++;
            }
        }
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */    
    if( contains(node1) && contains(node2) && node1 != node2){      
        if (node2->next == node1) {
            Node<T> *temp = node1;
            node1 = node2;
            node2 = temp;
        }
        if (node2->next != node1) {
            Node<T> *node1_p = node1->prev;
            Node<T> *node2_n = node2->next;

            if (node1->next == node2) {
                node1->prev = node1->next;
                node2->next = node2->prev;
                node2->prev = node1_p;
                node1->next = node2_n;
            } 
            else {
                node1->prev = node2->prev;
                node2->next = node1->next;
                node2->prev = node1_p;
                node1->next = node2_n;
            }          

            node1->prev->next = node1;
            node1->next->prev = node1;
            node2->prev->next = node2;
            node2->next->prev = node2;
        }
        if (head == node1){head = node2;}        
        else if (head == node2){head = node1;}
    }
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    for(int i=0; i<size ; i++){
        int index1 = i;
        int index2 = (i*i+seed)%size;
        //std::cout<<index1<<index2<<std::endl;
        this->swap(this->getNodeAtIndex(index1),this->getNodeAtIndex(index2));   
    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    if(this != &rhs){
        removeAllNodes();
        Node<T>* curr= rhs.getFirstNode();
        int s = rhs.getSize();        
        for(int i=0; i<s;i++){
            insertAtTheEnd(curr->data);
            curr = curr->next;
        }
    }    
    return *this;
}

#endif //LINKEDLIST_H
