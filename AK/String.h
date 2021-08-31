#pragma once
#include "Optional.h"
#include "StringView.h"
#include "Types.h"
#include "Vector.h"

usize strlen(char const* s);
void* memcpy(void* dst, void const* src, usize count);

class String {
public:
    explicit String() = default;
    explicit String(char const* s);
    explicit String(char const* s, usize length);
    explicit String(usize capacity);

    ~String();

    String(String const& other);
    String& operator=(String const& other);
    String(String&& other) noexcept;
    String& operator=(String&& other) noexcept;

    char const* c_str() { return m_data; }
    [[nodiscard]] Optional<char> get(usize i) const;
    Optional<StringView> substring() const;

    [[nodiscard]] Vector<String> split(char sep = ' ') const;

private:
    char* m_data { nullptr };
    usize m_length { 0 };
    usize m_capacity { 0 };
};