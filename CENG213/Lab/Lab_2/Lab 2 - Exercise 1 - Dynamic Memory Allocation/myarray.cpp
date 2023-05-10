#include "myarray.h"


//Set size to two and n to zero and set arr to point an array of two integers.
MyArray::MyArray()
{
    // TODO 
    this->size = 2;
    this->n = 0;
    this->arr = new int[2];
}

//Set size to two and n to one and set array to point an array of two integers
//The first element in the array must be first_el
MyArray::MyArray(int first_el)
{
    // TODO
    this->size = 2;
    this->n=1;
    this->arr = new int[2];
    this->arr[0]= first_el;
}

// Set size and n of the newly created MyArray same as  the size and n of rhs 
// Allocate new space and assign it to arr of the newly created MyArray
// Copy all elements in rhs to arr of the newly created MyArray
MyArray::MyArray(const MyArray& rhs)
{
    // TODO
    this->size = rhs.size;
    this->n = rhs.n;
    this->arr = new int[this->size]; 
    for(int i = 0; i< this->n; i++){
        this->arr[i] = rhs.arr[i];
        
    }
}

// Set size and n to zero and deallocate arr.
MyArray::~MyArray()
{
    // TODO
    n =0;
    size = 0;
    delete [] this->arr;
}

// Similar to copy constructor (i.e. deep copy semantics)
// Make sure you don't assign object to itself.
MyArray& MyArray::operator=(const MyArray& rhs)
{
    // TODO
    if(this == &rhs){
        return *this;
    }
    else{
        this->n = rhs.n;
        this->size = rhs.size;
        delete [] this->arr;
        this->arr = new int[size];
        for(int i=0; i<n; i++){
            this->arr[i] = rhs.arr[i];
            
        }
        return *this;
    }
}


// Allocate a bigger array of size (2*size).
// Copy n elements in arr to the new space.
// At the end of the function execution, arr must point to the bigger array 
// Set size correctly.
// Don't forget to delete the old space.
void MyArray::double_size()
{
    // TODO
    int *new_arr= new int[size * 2];
    for(int i=0; i<n; i++){
        new_arr[i]= this->arr[i];
    }
    this->size = size*2;
    delete [] this->arr;
    this->arr = new_arr;
}

// Check if arr is full
// If it is full double the size of arr (i.e. call double_size function)
// Insert element as the last item in the arr.
// Don't forget to increment n.
void MyArray::insert_data(int el)
{
    // TODO
    if(n == size){
        this->double_size();
    }
    int *new_array = new int[this->size];
    for(int i = 0; i< this->n; i++){
        new_array[i] = this->arr[i];
    }
    this->n += 1;
    new_array[this->n-1] = el;
    delete[] arr;
    this->arr = new_array;
}

// You can assume that ind >=0 and ind < n.
// Delete the element at ind, by shifting all elements after index ind
// one position to the left.
// You don't change the size but you must decrement n.
void MyArray::delete_data(int ind)
{
    // TODO
    for(int i= ind; i<n; i++){
        arr[i]= arr[i+1];
    }
    n -=1;
}

int MyArray::get_n()
{
    // TODO
    return n;
}

int MyArray::get_size()
{
    // TODO
    return size;
}

// gets the element in ind index where 0 <= ind < n. 
int MyArray::get_element(int ind)
{
    return arr[ind];
}

// Note that default parameters are only
// specified in the function declaration
// (not the definition, which is below).
void MyArray::print(char separator) const
{
    for (int i = 0; i < n-1; i++)
    {
        // We should use braces in "for", "if", "while"
        // constructs even if we have a single line
        // of code. This improves code clarity.
        
        std::cout << arr[i] << separator;
    }
    
    std::cout << arr[n-1] << std::endl;
}


