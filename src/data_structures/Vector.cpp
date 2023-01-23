#pragma once

#include "Vector.h"

template <class T>
void Vector<T>::setNewBuffer()
{
    T* temp = new T [capacity];
    for (short loop = 0; loop < lenght; loop++)
    {
        *temp = *buffer;
        buffer[loop].~T();
        temp++;
        buffer++;
    }
    temp -= lenght;
    buffer -= lenght;
    delete [] buffer;
    buffer = temp;
}

template <class T>
void Vector<T>::resizeIfNeccessary()
{
    if (lenght != capacity)
    {
        return;
    }

    Serial.println("RESIZE: "+String(lenght) + "  "+String(capacity));
    capacity += CAPACITY;
    setNewBuffer();
} 

template <class T>
void Vector<T>::clearMemoryIfNeccessary()
{
    if (capacity - lenght < CAPACITY+1)
    {
        return;
    }
    capacity = lenght+1;
    setNewBuffer();
}

template <class T>
void Vector<T>::push_back(T value)
{
    resizeIfNeccessary();
    Serial.println("bufer[len] = T value");
    buffer[lenght] = value;
    lenght++; 
}   

template <class T>
void Vector<T>::pop_back()
{
    clearMemoryIfNeccessary();
    lenght = lenght > 0 ? lenght - 1 : 0;
    buffer[lenght].~T();
} 

template <class T>
void Vector<T>::emplace(short idx, T value)
{
    this->buffer[idx] = value;
} 

template <class T>
bool Vector<T>::is_empty()
{
    return lenght == 0;
}

template <class T>
short Vector<T>::size()
{
    return lenght;
}

template <class T>
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
            *temp = *buf;
            temp++;
            buf++;
        }
        if (loop < lenght)
        {
            buffer[loop].~T();
        }
        
    }
    lenght = vec.size();
    temp -= lenght;
    buf -= lenght;
    delete [] buffer;
    buffer = temp;
}

template <class T>
T& Vector<T>::at(short idx)
{
    if (idx >= 0 && idx < lenght)
    {
        return buffer[idx];
    }
    T value;
    return value;
}

template <class T>
T& Vector<T>::operator[] (short idx)
{
    return buffer[idx];
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>& vec)
{
    swap(vec);
    return *this;
}

template <class T>
T* Vector<T>::buffer_()
{
    return buffer;
}

template <class T>
short Vector<T>::capacity_()
{
    return capacity;
}
