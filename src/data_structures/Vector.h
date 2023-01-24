#pragma once

#include "Arduino.h"

#define CAPACITY 40

template <class T>
class Vector
{
    short lenght;
    short capacity;
    T* buffer;

    void swap(Vector<T>& vec);
    void setNewBuffer();
    void clearMemoryIfNeccessary();
    void resizeIfNeccessary();
    public:

    template <class U, class... U2>
    Vector(U value, U2... rest) : Vector(rest...){
        push_back(value);
    }
    Vector() : capacity(capacity == 0 ? CAPACITY: 5), lenght(0) {
        buffer = new T [capacity];
    }

    ~Vector(){
        for (short i=0; i < lenght; i++)
        {
            buffer[i].~T();   
        }
        delete [] buffer;
    }

    /**
     * @brief Adds new value to the end of the Vector
     * 
     * @param value 
     */
    void
    push_back(T value);

    /**
     * @brief Deletes last element
     * 
     */
    void
    pop_back() noexcept;

    /**
     * @brief Checks wheter the Vector is empty
     * 
     * @return true 
     * @return false 
     */
    bool
    is_empty() noexcept;

    /**
     * @brief Changes previous value at idx to value
     * 
     * @param idx 
     * @param value 
     */
    void 
    emplace(short idx, T value);

    /**
     * @brief Returns current lenght of the Vector
     * 
     * @return short  
     */
    short 
    size() noexcept;

    /**
     * @brief 
     * 
     * @param idx 
     * @return T& 
     */
    T& 
    at(short idx);

    T* 
    buffer_() noexcept;

    short 
    capacity_() noexcept;

    T& operator[] (short idx);
    Vector& operator=(Vector& vec);
};