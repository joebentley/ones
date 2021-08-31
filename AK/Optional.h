#pragma once
#include "Types.h"
#include <cassert>
#include <memory>

template<typename T>
class Optional {
public:
    Optional() = default;

    //    Optional(const Optional& other)
    //        : m_has_value(other.m_has_value)
    //    {
    //        if (other.is_some())
    //            new (&m_storage) T(other.value());
    //    }
    //    Optional(Optional&& other) noexcept
    //        : m_has_value(other.m_has_value)
    //    {
    //        if (other.is_some())
    //            new (&m_storage) T(other.release_value());
    //    }

    Optional(const Optional& other) = delete;
    Optional(Optional&& other) = delete;

    template<typename U = T>
    explicit Optional(U&& value)
        : m_has_value(true)
    {
        new (&m_storage) T(std::forward<U>(value));
    }

    Optional& operator=(const Optional& other)
    {
        if (this != other) {
            clear();
            m_has_value = other.m_has_value;
            if (other.is_some()) {
                new (&m_storage) T(other.value());
            }
        }
        return *this;
    }

    Optional& operator=(Optional&& other) noexcept
    {
        if (this != other) {
            clear();
            m_has_value = other.m_has_value;
            if (other.is_some()) {
                new (&m_storage) T(other.release_value());
            }
        }
        return *this;
    }

    [[nodiscard]] bool is_some() const
    {
        return m_has_value;
    }
    [[nodiscard]] bool is_none() const
    {
        return !m_has_value;
    }

    [[nodiscard]] T& value()
    {
        return *(reinterpret_cast<T*>(&m_storage));
    }

    [[nodiscard]] const T& value() const
    {
        return *(reinterpret_cast<const T*>(&m_storage));
    }

    [[nodiscard]] T
    release_value()
    {
        assert(m_has_value);
        T released_value = std::move(value());
        value().~T();
        m_has_value = false;
        return released_value;
    }

    void clear()
    {
        if (m_has_value) {
            value().~T();
            m_has_value = false;
        }
    }

private:
    u8 m_storage[sizeof(T)] {};
    bool m_has_value { false };
};
