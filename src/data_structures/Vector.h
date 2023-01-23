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

    void push_back(T value);
    void pop_back();
    bool is_empty();
    void emplace(short idx, T value);
    short size();
    T& at(short idx);
    T* buffer_();
    short capacity_();


    T& operator[] (short idx);
    Vector& operator=(Vector& vec);
};