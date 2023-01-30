#pragma once

#include "Arduino.h"

#define CAPACITY 12

template <typename T>
class Vector
{
    short lenght;
    short capacity;
    T* buffer;

    void 
    swap(Vector<T>& vec);

    void 
    setNewBuffer();

    void 
    clearMemoryIfNeccessary();

    void 
    resizeIfNeccessary();

    public:

    template <typename U, typename... U2>
    Vector(U value, U2... rest) : Vector(rest...){
        push_back(value);
    }
    Vector() : capacity(CAPACITY), lenght(0) {
        this->buffer = new T [capacity];
    }

    ~Vector(){
        for (short i=0; i < lenght; i++)
        {
            (this->buffer+i)->~T();   
        }
        delete [] this->buffer;
    }

    /**
     * @brief Adds new value to the end of the Vector
     * 
     * @param value 
     */
    void
    push_back(T& value);

    /**
     * @brief Deletes last element
     * 
     */
    void
    pop_back() noexcept;

    /**
     * @brief Checks wheter the Vector is empty,
     * size == 0
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
     * @brief Same as [idx] 
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