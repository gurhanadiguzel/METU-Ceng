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

    KeyedHashTable ht0(30);

    std::string findKey = "Watch me I am going to find this string";

    ht0.Insert("Val", testList2);
    ht0.Insert("TestString", testList1);
    ht0.Insert("VeryVeryLongTestString", testList2);
    ht0.Insert("Writing this on QWERTY Keyboard", testList1);
    ht0.Insert(findKey, testList0);
    ht0.Print();

    ht0.ClearTable();
    std::cout << "========After Clear========\n";
    ht0.Print();
}

int main()
{
    PA3_HT_TEST_CASE tc;
    tc();
}