#include <iostream>

#include "LinkedList.h"
#include "Album.h"
#include "Artist.h"
#include "Profile.h"
#include "Song.h"
#include "MusicStream.h"

int main() {
    LinkedList<int> llist;
    LinkedList<int> llist1; 
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(5);
    llist.insertAtTheFront(3);    
    llist.insertAtTheFront(2);
    llist.insertAtTheFront(1); 

    llist.print();
    llist1 = llist ;
    std::cout<<" size "<<llist.getSize()<<std::endl;
    std::cout<<"  "<<std::endl; 

    llist1=llist;  
    llist1.print();
    std::cout<<" size "<<llist1.getSize()<<std::endl;
    std::cout<<"  "<<std::endl;            
    

    llist.insertAfterNode(9, llist.getNode(8));
    llist.print();
    std::cout<<" size "<<llist.getSize()<<std::endl;
    std::cout<<"  "<<std::endl;

    llist.insertAsEveryKthNode(0,2);
    llist.print();
    std::cout<<" size "<<llist.getSize()<<std::endl;;
    std::cout<<"  "<<std::endl;

    llist.removeNode(llist.getNodeAtIndex(0));
    llist.print();
    std::cout<<" size "<<llist.getSize()<<std::endl;
    std::cout<<"  "<<std::endl;
    llist.print(true); 


    llist.removeAllNodes();    
    llist.removeNode(8);
    std::cout<<"  "<<std::endl;
    llist.print();

    llist.removeEveryKthNode(2);
    llist.print(); 
    std::cout<<"  "<<std::endl; 
     
    llist.swap(llist.getNodeAtIndex(2),llist.getNodeAtIndex(1));
    llist.print();
    std::cout<<" size "<<llist.getSize()<<std::endl;
    std::cout<<"  "<<std::endl;

    llist.shuffle(5);
    std::cout<<" L "<<std::endl;
    llist.print(); 
    std::cout<<"  "<<std::endl;
    
   llist.swap(llist.getNodeAtIndex(1),llist.getNodeAtIndex(6));
    llist.print();
    std::cout<<" size "<<llist.getSize()<<std::endl;
    std::cout<<"  "<<std::endl;

/*    MusicStream alist;
    std::string t = "BLABLA" ;
    std::string t1 = "BLABLA" ;
    const std::string  &s = t;
    const std::string &d = t1; 
    list.addProfile(s,d,premium);
    alist.MusicStream::print();*/
    

    return 0;
}
