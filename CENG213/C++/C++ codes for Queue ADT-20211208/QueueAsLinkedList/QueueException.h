#ifndef _EXCEPTION
#define _EXCEPTION
#include <string>
using namespace std;

class QueueException {
public:
    QueueException(string err){
	       error = err;
    }
    string error;

};
#endif // _EXCEPTION


