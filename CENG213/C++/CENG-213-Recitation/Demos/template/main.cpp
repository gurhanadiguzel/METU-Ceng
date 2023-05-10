#include "SharedPtr.h"

int main()
{
    SharedPtr<int> p = SharedPtr<int>(33);

    p.Test(6);
    std::cout<< p.refCount << std::endl;

    p.print();
}