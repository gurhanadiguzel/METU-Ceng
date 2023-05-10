#include "HashTable.h"
#include <iostream>

class PA3_HT_TEST_CASE
{
    public:
        void operator()() const;
};

void PA3_HT_TEST_CASE::operator()() const
{
    KeyedHashTable ht0(12);

    ht0.Insert("Val", std::vector<int>());

    std::vector<int> testList;
    testList.push_back(1);
    testList.push_back(2);
    testList.push_back(3);
    ht0.Insert("L", testList);

    ht0.Print();
}

int main()
{
    PA3_HT_TEST_CASE tc;
    tc();
}