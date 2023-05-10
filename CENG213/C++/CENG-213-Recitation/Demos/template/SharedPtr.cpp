#include "SharedPtr.h"

// template <class T>
// SharedPtr<T>::SharedPtr(const SharedPtr& rhs)
// {
//     ptr = rhs.ptr;
//     //rhs.refCount++;
//     refCount++;
// }

// template <class T>
// SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& rhs)
// {
//     ptr = rhs.ptr;
//     //rhs.refCount++;
//     refCount++;
// }

// template <class T>
// SharedPtr<T>::~SharedPtr()
// {
//     refCount--;
//     if(refCount == 0)
//         delete ptr;
// }

// template <class T>
// T* SharedPtr<T>::get_ptr()
// {
//     return ptr;
// }

// template <class T>
// const T* SharedPtr<T>::get_ptr() const
// {
//     return ptr;
// }

// template <class T>
// void SharedPtr<T>::print() const
// {
//     std::cout << *ptr << std::endl;
// }