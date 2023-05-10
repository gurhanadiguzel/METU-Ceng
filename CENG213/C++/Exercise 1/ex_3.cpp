#include <iostream>

using namespace std;

void fun1(int &a, int &b){
    int temp;
    temp=a;
    a=b;
    b=temp;
    

}

int main(){
    cout << "Hello World" << endl;
    int n=5, m=6;
    int &rn=n;
    int*p =&n;
    n=6;
    rn=7;
    cout << n << rn << endl;
    cout << &rn <<" ," << &n<<", " << *p<<", " << p<<" ," << &p<<", " << endl;

    for(int i=0; i<4; i++){
        cout << i << endl;
    }
    
    int x=0;
    int y=3;
    fun1(x,y);
    cout << x << " " << y << endl;
    return 0;
}
