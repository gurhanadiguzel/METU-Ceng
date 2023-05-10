#include <iostream>
template <typename T>
//template <class T>
class SharedPtr
{
private:
    T* ptr;
    int refCount;

    void Test(int i);

public:
    SharedPtr(T data);
    SharedPtr(const SharedPtr&);
    SharedPtr& operator=(const SharedPtr&);
    ~SharedPtr();

    T*        get_ptr();
    const T*  get_ptr() const;

    void      print() const;

    void      SetT(T*);
};

template <class T>
void SharedPtr<T>::Test(int i)
{
    refCount = i;
}

template <class T>
SharedPtr<T>::SharedPtr(T data)
{
    ptr = new T();
    *ptr = data;
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& rhs)
{
    ptr = rhs.ptr;
    //rhs.refCount++;
    refCount++;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& rhs)
{
    ptr = rhs.ptr;
    //rhs.refCount++;
    refCount++;
}

template <class T>
SharedPtr<T>::~SharedPtr()
{
    refCount--;
    if(refCount == 0)
        delete ptr;
}

template <class T>
T* SharedPtr<T>::get_ptr()
{
    return ptr;
}

template <class T>
const T* SharedPtr<T>::get_ptr() const
{
    return ptr;
}

template <class T>
void SharedPtr<T>::print() const
{
    std::cout << *ptr << std::endl;
}