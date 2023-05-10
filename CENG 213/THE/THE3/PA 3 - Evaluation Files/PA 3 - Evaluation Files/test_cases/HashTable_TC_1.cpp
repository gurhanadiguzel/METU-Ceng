#include "HashTable.h"
#include <iostream>

//#define TEST_AMOUT 540
#define TEST_AMOUT 30

class PA3_HT_TEST_CASE
{
    private:
        static bool    isPrime(int i);

    public:
        void           operator()() const;
};

bool PA3_HT_TEST_CASE::isPrime(int number)
{
    if(number == 0 || number == 1)
        return false;

    // Numbers are relatively small so just brute force it
    for(int i = 0; i < PRIME_TABLE_COUNT; i++)
    {
        int prime = KeyedHashTable::PRIME_LIST[i];
        if(i >= prime) return true;

        if(number % prime == 0)
            return false;
    }
    return true;
}

void PA3_HT_TEST_CASE::operator()() const
{
    for(int i = 0; i < TEST_AMOUT; i++)
    {
        int result = KeyedHashTable::FindNearestLargerPrime(i);

        if(result <= i)
        {
            std::cout << "Prime should be greater than " << i;
            std::cout << ". Result" << result << "\n";
        }
        // Check if there is a better prime in between
        else for(int j = i + 1; j < result; j++)
        {
            if(isPrime(j))
            {
                std::cout << "There is a better prime: " << j;
                std::cout << "Your prime: " << result << "\n";
                return;
            }
        }
    }
    std::cout << "Prime Test Passed" << std::endl;
}

int main()
{
    PA3_HT_TEST_CASE testCase;
    testCase();
}