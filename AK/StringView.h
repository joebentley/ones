#pragma once
#include "Types.h"

class StringView {
    StringView(char const* s, usize length)
        : m_data(s)
        , m_length(length)
    {
    }

private:
    char const* m_data;
    usize m_length;
};
