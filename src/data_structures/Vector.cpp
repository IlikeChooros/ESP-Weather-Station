#pragma once

#include "Vector.h"

template <typename T>
void Vector<T>::setNewBuffer()
{
    T* temp = new T [capacity];
    for (short loop = 0; loop < lenght; loop++)
    {
        *(temp+loop)= *(buffer+loop); // faster than temp[i] = buffer[i]
        (buffer+loop)->~T();
    }
    delete [] buffer;
    buffer = temp;
}

template <typename T>
void Vector<T>::resizeIfNeccessary()
{
    if (lenght != capacity)
    {
        return;
    }
    capacity += CAPACITY;
    setNewBuffer();
} 

template <typename T>
void Vector<T>::clearMemoryIfNeccessary()
{
    if (capacity - lenght < CAPACITY+1)
    {
        return;
    }
    capacity = lenght+1;
    setNewBuffer();
}

template <typename T>
void Vector<T>::push_back(T& value)
{
    resizeIfNeccessary();
    buffer[lenght] = value;
    lenght++; 
}   

template <typename T>
void Vector<T>::pop_back() noexcept
{
    clearMemoryIfNeccessary();
    lenght = lenght > 0 ? lenght - 1 : 0;
    (buffer + lenght)->~T();
} 

template <typename T>
void Vector<T>::emplace(short idx, T value)
{
    *(buffer + idx) = value;
} 

template <typename T>
bool Vector<T>::is_empty() noexcept
{
    return lenght == 0;
}

template <typename T>
short Vector<T>::size() noexcept
{
    return lenght;
}

template <typename T>
void Vector<T>::swap(Vector<T>& vec)
{
    T* buf = vec.buffer_();
    capacity = vec.capacity_();
    short max_lenght = lenght < vec.size() ? vec.size() : lenght;

    T* temp = new T [capacity];
    for (short loop = 0; loop < max_lenght; loop++)
    {
        if (loop < vec.size())
        {
            *(temp+loop) = *(buf+loop);
        }
        if (loop < lenght)
        {
            (buffer + loop)->~T();
        }
        
    }
    lenght = vec.size();
    delete [] buffer;
    buffer = temp;
}

template <typename T>
T& Vector<T>::at(short idx)
{
    if (idx >= 0 && idx < lenght)
    {
        return *(buffer+idx);
    }
    T value;
    return value;
}

template <typename T>
T& Vector<T>::operator[] (short idx)
{
    return *(buffer + idx);
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>& vec)
{
    swap(vec);
    return *this;
}

template <typename T>
T* Vector<T>::buffer_() noexcept
{
    return buffer;
}

template <typename T>
short Vector<T>::capacity_() noexcept
{
    return capacity;
}