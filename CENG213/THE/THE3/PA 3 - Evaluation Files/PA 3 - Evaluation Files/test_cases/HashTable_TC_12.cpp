#include "HashTable.h"
#include <iostream>

class PA3_HT_TEST_CASE
{
    public:
        void operator()() const;
};

void PA3_HT_TEST_CASE::operator()() const
{
    std::vector<int> vctr;

    // Start with default table
    // (So it will ReHash many times)

    KeyedHashTable ht0(50);
    // Hash Value 666
    ht0.Insert("ACC", vctr);
    ht0.Insert("EBB", vctr);
    ht0.Insert("IAA", vctr);
    ht0.Print();
    ht0.Remove("EBB");
    ht0.Print();
}

int main()
{
    PA3_HT_TEST_CASE tc;
    tc();
}