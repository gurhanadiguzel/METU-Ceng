#include "pair.hpp"

/*              Default Constructor for Pair Class    */
Pair::Pair(int p1, int p2)
{
    pa=new int;
    pb=new int;
    *pa=p1;
    *pb=p2;
    /* TO-DO */
}


/*              Copy Constructor for Pair Class    */
Pair::Pair(const Pair &p) 
{
    pa= new int;                
    pb= new int;
    *pa = *(p.pa);
    *pb = *(p.pb); 
    /* TO-DO */
}

/*                    Destructor for Matrix Class  */
Pair::~Pair()
{
    delete pa;
    delete pb;
    /* TO-DO */
}

