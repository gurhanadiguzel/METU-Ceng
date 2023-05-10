#include "HashTable.h"
#include <iostream>

class PA3_HT_TEST_CASE
{
    public:
        void operator()() const;
};

void PA3_HT_TEST_CASE::operator()() const
{
    bool passed = true;

    KeyedHashTable ht0(8);
    if(ht0.occupiedElementCount != 0)
    {
        std::cout << "Failed on HT Constructor KeyedHashTable(8) \n";
        std::cout << "ht.occupiedEmentCount should be 0 was "
                  << ht0.occupiedElementCount << "\n";
        passed &= false;
    }
    if(ht0.tableSize != 11)
    {
        std::cout << "Failed HT Constructor KeyedHashTable(8) \n";
        std::cout << "ht.tableSize should be 11 was " << ht0.tableSize << "\n";
        passed &= false;
    }

    // Give a prime (it should give the next prime)
    KeyedHashTable ht1(23);
    if(ht1.occupiedElementCount != 0)
    {
        std::cout << "Failed on HT Constructor KeyedHashTable(23) \n";
        std::cout << "ht.occupiedEmentCount should be 0 was "
                  << ht1.occupiedElementCount << "\n";
        passed &= false;
    }
    if(ht1.tableSize != 29)
    {
        std::cout << "Failed HT Constructor KeyedHashTable(23) \n";
        std::cout << "ht.tableSize should be 29 was " << ht1.tableSize << "\n";
        passed &= false;
    }

    if(passed) std::cout << "Test Passed" << std::endl;
}

int main()
{
    PA3_HT_TEST_CASE tc;
    tc();
}