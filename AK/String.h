#pragma once
#include "Types.h"

class String {
public:
    explicit String(char const* s);
    explicit String(usize capacity);

    ~String();

    String(String const& other);
    String& operator=(String const& other);
    String(String&& other) noexcept;
    String& operator=(String&& other) noexcept;

    char const* c_str() { return m_data; }

private:
    char* m_data;
    usize m_length { 0 };
    usize m_capacity { 0 };
};