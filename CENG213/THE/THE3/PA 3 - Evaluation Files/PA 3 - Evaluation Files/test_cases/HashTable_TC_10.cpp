#include "HashTable.h"
#include <iostream>

class PA3_HT_TEST_CASE
{
    private: void CheckPrintReHash(const KeyedHashTable&, int tableSize) const;
    public:
        void operator()() const;
};

void PA3_HT_TEST_CASE::CheckPrintReHash(const KeyedHashTable& ht,
                                        int tableSize) const
{
    if(ht.tableSize != tableSize)
        std::cout << "Wrong table size " << ht.tableSize
                  << " should be " << tableSize << "\n";
}

void PA3_HT_TEST_CASE::operator()() const
{
    std::vector<int> vctr;

    // Start with default table
    // (So it will ReHash many times)

    KeyedHashTable ht0;
    ht0.Insert("A", vctr);
    // Should be rehashed (only check size)
    CheckPrintReHash(ht0, 5);

    ht0.Insert("B", vctr);
    // Should be rehashed (only check size)
    CheckPrintReHash(ht0, 11);

    ht0.Insert("C", vctr);
    ht0.Insert("D", vctr);
    // Should be rehashed (only check size)
    CheckPrintReHash(ht0, 23);

    ht0.Insert("E", vctr);
    ht0.Insert("F", vctr);
    ht0.Insert("G", vctr);
    ht0.Insert("H", vctr);
    // Should be rehashed (only check size)
    CheckPrintReHash(ht0, 47);

    ht0.Insert("I", vctr);
    ht0.Insert("J", vctr);
    ht0.Insert("K", vctr);
    ht0.Insert("L", vctr);
    ht0.Insert("M", vctr);
    ht0.Insert("N", vctr);
    ht0.Insert("O", vctr);
    ht0.Insert("P", vctr);
    // Should be rehashed (only check size)
    CheckPrintReHash(ht0, 97);

    ht0.Print();
}

int main()
{
    PA3_HT_TEST_CASE tc;
    tc();
}