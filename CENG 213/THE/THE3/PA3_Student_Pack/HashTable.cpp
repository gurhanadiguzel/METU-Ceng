#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const{
    // TODO
    int hashval = 0;
    for(int i=0; i< key.length(); i++){
        hashval += (PRIME_LIST[i]*key[i]);
    }    
    hashval %= tableSize;
    if (hashval < 0){
        hashval += tableSize;
    }
    return hashval;
}

void KeyedHashTable::ReHash(){
    // TODO
    int new_prime = FindNearestLargerPrime(tableSize*2);  
    HashData* new_table = new HashData[new_prime];
    int old_size =tableSize;
    tableSize = new_prime;
    for(int i=0; i<old_size; i++){
        int hashcode = Hash(table[i].key);
        int quad = 1;
        while(new_table[hashcode].key != ""){
            hashcode = hashcode + (2*quad-1);
            hashcode %= tableSize;
            quad++;
        }
        if(new_table[hashcode].key == ""){
            new_table[hashcode].key = table[i].key;
            new_table[hashcode].intArray = table[i].intArray;
        }
    }    
    delete [] table;
    table = new_table;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity){
    // TODO
    for(int i=0; i<PRIME_TABLE_COUNT; i++){
        if(PRIME_LIST[i]> requestedCapacity){
            return PRIME_LIST[i];
        }
    }
}

KeyedHashTable::KeyedHashTable(){
    // TODO
    tableSize = 2;
    table = new HashData[2];
    for(int i= 0; i<tableSize ; i++){
        table[i].key = "";
        table[i].intArray = std::vector<int>();
    }
    occupiedElementCount =0;
}

KeyedHashTable::KeyedHashTable(int requestedCapacity){
    // TODO
    tableSize = FindNearestLargerPrime(requestedCapacity);
    table = new HashData[tableSize];
    for(int i= 0; i<tableSize ; i++){
        table[i].key = "";
        table[i].intArray = std::vector<int>();
    }
    occupiedElementCount =0;
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other){
    // TODO
    this->table = new HashData[other.tableSize];
    for(int i=0; i<other.tableSize; i++){
        table[i].key = other.table[i].key;
        table[i].intArray = other.table->intArray;
    }
    tableSize = other.tableSize;
    occupiedElementCount= other.occupiedElementCount;       
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other){
    // TODO
    if(this != &other){
        delete [] this->table;
        this->table = new HashData[other.tableSize];
        for(int i=0; i<other.tableSize; i++){
            table[i].key = other.table[i].key;
            table[i].intArray = other.table->intArray;
        }
        tableSize = other.tableSize;
        occupiedElementCount= other.occupiedElementCount; 
    }
    return *this;
}

KeyedHashTable::~KeyedHashTable(){
    // TODO
    delete [] table;    
    tableSize = 0;
    occupiedElementCount = 0;
}

bool KeyedHashTable::Insert(const std::string& key, const std::vector<int>& intArray){
    // TODO
    int hashcode = Hash(key);
    int quad = 1;
    while(table[hashcode].key != "" && table[hashcode].key != "__DELETED__" && table[hashcode].key!= key){
        hashcode = hashcode + (2*quad-1);
        hashcode %= tableSize;
        quad++;
    }
    if(table[hashcode].key == key){
        return false;
    }
    if(table[hashcode].key != key){
        table[hashcode].key = key;
        table[hashcode].intArray = intArray;
        occupiedElementCount++;
    }
    if(occupiedElementCount * EXPAND_THRESHOLD >= tableSize){
        ReHash();
    }
    return true;
}

bool KeyedHashTable::Remove(const std::string& key){
    // TODO
    bool flag = false;
    int hashcode = Hash(key);
    int quad = 1;
    while(table[hashcode].key != "" && table[hashcode].key != key){
        hashcode = hashcode + (2*quad-1);
        hashcode %= tableSize;
        quad++;
    }
    if(table[hashcode].key == key){
        table[hashcode].key = "__DELETED__";
        table[hashcode].intArray.clear();
        occupiedElementCount--;
        flag = true;
    }
    return flag;
}

void KeyedHashTable::ClearTable(){
   // TODO
   for(int i=0; i<tableSize; i++){
       table[i].key = "";
       table[i].intArray.clear();
   }
   occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,const std::string& key) const{
    // TODO
    int hashcode = Hash(key);
    int quad = 1;
    while (table[hashcode].key != "") {
        if (table[hashcode].key == key){ 
            valueOut = table[hashcode].intArray;
            return true;
        }
        hashcode = hashcode + (2*quad-1);
        hashcode %= tableSize;
        quad++;
    }
    return false;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}