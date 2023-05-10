#include "HashTable.h"
#include <iostream>

class PA3_HT_TEST_CASE
{
    public:
        void operator()() const;
};

void PA3_HT_TEST_CASE::operator()() const
{
    std::vector<int> testList0;
    testList0.push_back(1);
    testList0.push_back(2);
    testList0.push_back(3);
    std::vector<int> testList1;
    testList1.push_back(3);
    testList1.push_back(0);
    testList1.push_back(1);
    std::vector<int> testList2;

    KeyedHashTable ht0(12);

    ht0.Insert("Val", testList0);
    ht0.Insert("TestString", testList1);
    ht0.Insert("VeryVeryLongTestString", testList2);
    ht0.Print();
    std::cout << "================\n";
    // Copy Constructor
    KeyedHashTable ht1(8);
    ht1.Insert("Good", testList1);
    ht1.Insert("Bad", testList0);
    ht1.Print();

    std::cout << "========After Assignment (HT0 = HT1)========\n";
    ht0 = ht1;
    ht0.Print();

    std::cout.flush();
}

int main()
{
    PA3_HT_TEST_CASE tc;
    tc();
}