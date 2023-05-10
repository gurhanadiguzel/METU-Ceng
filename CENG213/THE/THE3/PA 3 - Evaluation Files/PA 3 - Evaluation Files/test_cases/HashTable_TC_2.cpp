#include "HashTable.h"
#include <iostream>

//#define TEST_AMOUT 540
#define TEST_AMOUT 30

class PA3_HT_TEST_CASE
{
    private: static int HashReference(const std::string&,
                                      int tableSize);

    public: void operator()() const;
};

int PA3_HT_TEST_CASE::HashReference(const std::string& s, int tableSize)
{
    int hashValue = 0;
    for(size_t i = 0; i < s.size(); i++)
    {
        hashValue += static_cast<int>(s[i] * KeyedHashTable::PRIME_LIST[i]);
    }
    return hashValue % tableSize;
}

void PA3_HT_TEST_CASE::operator()() const
{
    KeyedHashTable ht(12);
    int tableSize = 13;

    const std::string STRINGS[4] =
    {
        std::string("Val"),
        std::string("laV"),
        std::string("Test"),
        std::string("Ankara")
    };

    const int RESULTS[4] =
    {
        HashReference(STRINGS[0], tableSize),
        HashReference(STRINGS[1], tableSize),
        HashReference(STRINGS[2], tableSize),
        HashReference(STRINGS[3], tableSize)
    };

    const int TEST_OUTS[4] =
    {
        ht.Hash("Val"),
        ht.Hash("laV"),
        ht.Hash("Test"),
        ht.Hash("Ankara")
    };

    bool passed = true;
    for(int i = 0; i < 4; i++)
    {
        if(RESULTS[i] != TEST_OUTS[i])
        {
            std::cout << "Test Fail for " << STRINGS[i] << ": ";
            std::cout << "Output was " << TEST_OUTS[i] << ", should be" << RESULTS[i];
            std::cout << "\n";
            passed &= false;
        }
    }

    if(passed) std::cout << "Hash Test Passed" << std::endl;
}

int main()
{
    PA3_HT_TEST_CASE testCase;
    testCase();
}