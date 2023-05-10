#ifndef _EXCEPTION
#define _EXCEPTION
#include <string>
using namespace std;

class StackException {
public:
    StackException(string err){
	       error = err;
    }
    string error;

};
#endif // _EXCEPTION
