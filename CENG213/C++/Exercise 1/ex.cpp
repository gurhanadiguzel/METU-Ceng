#include <iostream>

using namespace std;

int main(){
    int p1 =5, p2=6;
    int *pa=new int;
    int *pb=new int;
    *pa=p1;
    *pb=p2;
    cout << *pa << *pb << endl;
}