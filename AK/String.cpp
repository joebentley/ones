#include "String.h"

usize strlen(char const* s)
{
    usize i = 0;
    while (*s++ != '\0')
        i++;
    return i;
}

void* memcpy(void* dst, void const* src, usize count)
{
    char* dstArray = (char*)dst;
    char const* srcArray = (char const*)src;
    while (count-- > 0)
        dstArray[count] = srcArray[count];
    return (void*)dstArray;
}

String::String(char const* s)
    : String(strlen(s))
{
    m_length = strlen(s);
    m_data = (char*)memcpy(m_data, s, m_length);
}

String::String(std::size_t capacity)
    : m_capacity(capacity)
{
    m_data = new char[m_capacity](); // Zero initialized
}

String::~String()
{
    delete[] m_data;
}

String::String(String const& other)
{
    m_capacity = other.m_capacity;
    m_length = other.m_length;
    m_data = new char[m_capacity]();

    for (usize i = 0; i < other.m_capacity; i++) {
        m_data[i] = other.m_data[i];
    }
}

String& String::operator=(String const& other)
{
    return *this = String(other);
}

String::String(String&& other) noexcept
{
    m_capacity = other.m_capacity;
    m_length = other.m_length;
    m_data = other.m_data;
    other.m_data = nullptr;
}

String& String::operator=(String&& other) noexcept
{
    m_capacity = other.m_capacity;
    m_length = other.m_length;
    m_data = other.m_data;
    other.m_data = nullptr;
    return *this;
}
