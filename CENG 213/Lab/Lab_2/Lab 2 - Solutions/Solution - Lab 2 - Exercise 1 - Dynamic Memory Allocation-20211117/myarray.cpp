#include "myarray.h"

//Set size to two and n to zero and set arr to point an array of two integers.
MyArray::MyArray()
{
    arr = new int[2];
    n = 0;
    size = 2;
}

//Set size to two and n to one and set array to point an array of two integers
//The first element in the array must be first_el
MyArray::MyArray(int first_el)
{
    arr = new int[2];
    size = 2;
    arr[0] = first_el;
    n = 1;
}

// Set size and n of the newly created MyArray same as  the size and n of rhs
// Allocate new space and assign it to arr of the newly created MyArray
// Copy all elements in rhs to arr of the newly created MyArray
MyArray::MyArray(const MyArray& rhs)
{
    arr = new int [rhs.size];
    size = rhs.size;
    
    // Copy the data from "rhs" to the current object
    for (int i = 0; i < rhs.n; i++)
    {
        arr[i] = rhs.arr[i];
    }
    n = rhs.n;
}

// Set size and n to zero and deallocate arr.
MyArray::~MyArray()
{
    // Deallocate the data. It is safe to delete a NULL
    // pointer so we don't need to check if data == NULL
    // before doing a delete.
    delete[] arr;
}

// Similar to copy constructor (i.e. deep copy semantics)
// Make sure you don't assign object to itself.
MyArray& MyArray::operator=(const MyArray& rhs)
{
    // Note that every object has a pointer called "this",
    // which points to the object itself. Here, we used
    // this to check for self-assignment such as myarray1 = myarray1.
    if (this != &rhs)
    {
        // Deallocate the previous data
        delete[] arr;
        
        // Allocate for the new data
        arr = new int [rhs.size];
        size = rhs.size;
        
        // Copy the data from "rhs" to the current object
        for (int i = 0; i < rhs.n; i++)
        {
            arr[i] = rhs.arr[i];
        }
        n = rhs.n;
    }
    
    // Again we are using "*this" to return the current
    // object.
    return *this;
}

// Allocate a bigger array of size (2*size).
// Copy n elements in arr to the new space.
// At the end of the function execution, arr must point to the bigger array
// Set size correctly.
// Don't forget to delete the old space.
void MyArray::double_size()
{
    // Allocate new space for arr.
    int* new_arr = new int [size*2];
    
    // Copy arr content to new space.
    for (int i=0; i<n; i++) {
        new_arr[i] = arr[i];
    }
    
    // Deallocate old space.
    delete[] arr;
    
    // Assign new space to arr member and update size.
    arr = new_arr;
    size *= 2;
}

// Check if arr is full
// If it is full double the size of arr (i.e. call double_size function)
// Insert element as the last item in the arr.
// Don't forget to increment n.
void MyArray::insert_data(int el)
{
    // If the array is full, double allocated space.
    if (size == n) {
        double_size();
    }
    
    // Insert el to the end of arr and update n.
    arr[n] = el;
    n++;
}

// You can assume that ind >=0 and ind < n.
// Delete the element at ind, by shifting all elements after index ind
// one position to the left.
// You don't change the size but you must decrement n.
void MyArray::delete_data(int ind)
{
    // Delete arr[ind] by shifting all items to the left from index ind+1
    // to index n.
    for (int i=ind; i<n-1; i++)
    {
        arr[i] = arr[i+1];
    }
    
    // Decrement n to exclude old copy of the last shifted item from the array.
    n--;
}

int MyArray::get_n()
{
    return n;
}

// returns size
int MyArray::get_size()
{
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


