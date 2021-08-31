#include "ReadonlyFileBuffer.h"

Optional<ReadonlyFileBuffer> ReadonlyFileBuffer::from_file(char const* filename)
{
    return {};
}

Optional<u8> ReadonlyFileBuffer::get_byte(std::size_t at)
{
    return m_bytes.get(at);
}
