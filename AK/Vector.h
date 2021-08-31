#pragma once
#include "Optional.h"
#include "String.h"
#include "Types.h"
#include <cmath>

template<typename T>
class Vector {
public:
    explicit Vector(usize capacity)
        : m_capacity(capacity)
    {
        m_array = new T[capacity];
    }

    Vector(Vector const& other)
    {
        Vector v = other;
        return v;
    }
    Vector& operator=(Vector const& other)
    {
        if (this != &other) {
            memcpy(m_array, other.m_array, m_length);
            m_length = other.m_length;
            m_capacity = other.m_capacity;
        }
        return *this;
    }
    Vector(Vector&& other) noexcept
    {
        Vector v = other;
        return v;
    }
    Vector& operator=(Vector&& other) noexcept
    {
        m_array = other.m_array;
        m_length = other.m_length;
        m_capacity = other.m_capacity;
        other.m_array = nullptr;
        other.m_length = 0;
        other.m_capacity = 0;
        return *this;
    }

    void resize(usize capacity)
    {
    }
    Optional<T*> get(usize i)
    {
        if (i >= m_length)
            return {};
        return { &m_array[i] };
    }
    void push(const T& value)
    {
    }
    void push(T&& value)
    {
    }

    ~Vector()
    {
        delete[] m_array;
    }

private:
    usize m_length { 0 };
    usize m_capacity { 0 };
    T* m_array;
};
