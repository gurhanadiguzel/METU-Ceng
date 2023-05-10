#include <iostream>
using namespace std;
int *a(){
    int z = 0;
    return &z;
}
int main(){
    int *j;
    j=a();
    int k= *j;
    cout<<k;
    return 0;
}