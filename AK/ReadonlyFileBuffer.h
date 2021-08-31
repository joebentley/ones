#pragma once
#include "Macros.h"
#include "Optional.h"
#include "Types.h"
#include "Vector.h"
#include <cstdio>

class ReadonlyFileBuffer {
public:
    NON_COPYABLE(ReadonlyFileBuffer);
    NON_MOVABLE(ReadonlyFileBuffer);

    static Optional<ReadonlyFileBuffer> from_file(char const* filename);

    Optional<u8> get_byte(usize at);

private:
    Vector<u8> m_bytes;
};