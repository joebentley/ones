#include "NesFileParser.h"
#include <fmt/core.h>

#define TRY_GET(name, return_fail) \
    if (is_eof()) {                \
        return return_fail;        \
    }                              \
    u8 name = get();

bool get_bit(u8 d, u8 i)
{
    return (d & (0b1 << i)) > 0;
}

bool NesFileParser::parse_magic()
{
    m_fs->seekg(0);

    std::vector<u8> expected = { 0x4E, 0x45, 0x53, 0x1A };
    std::vector<u8> actual;

    for (int i = 0; i < 4; i++) {
        TRY_GET(b, false)
        actual.push_back(b);
    }

    return actual == expected;
}

std::optional<NesHeader> NesFileParser::parse_header()
{
    if (!parse_magic())
        return {};

    NesHeader header {};
    TRY_GET(prg_size, {})
    TRY_GET(chr_size, {})
    TRY_GET(flags_six, {})
    TRY_GET(flags_seven, {})

    header.m_prg_rom_size = prg_size;
    header.m_chr_rom_size = chr_size;

    header.m_vertical_mirror = get_bit(flags_six, 0);
    header.m_has_save = get_bit(flags_six, 1);
    header.m_has_trainer = get_bit(flags_six, 2);
    header.m_ignore_mirroring = get_bit(flags_six, 3);
    header.m_mapper = ((flags_seven & 0xF0) << 4) | (flags_six & 0xF0);

    // Skip flags 8, 9, 10
    m_fs->seekg(11);

    header.m_ripper_name = std::string(4, '\0');
    m_fs->read(&header.m_ripper_name[0], 4);

    if (header.m_ripper_name[0] == '\0')
        header.m_ripper_name.clear();

    return header;
}

#define RETURN_BYTES(offset_var, size)        \
    m_fs->seekg(offset_var);                  \
                                              \
    auto bytes = std::vector<u8>(size, '\0'); \
    for (size_t i = 0; i < (size); i++) {     \
        if (is_eof()) {                       \
            return {};                        \
        }                                     \
        bytes[i] = static_cast<u8>(get());    \
    }                                         \
                                              \
    return bytes;

std::optional<std::vector<u8>> NesFileParser::read_prg_rom(NesHeader const& header)
{
    std::istream::pos_type offset = header.m_has_trainer ? 512 : 0;
    RETURN_BYTES(offset, header.m_prg_rom_size * 16384)
}

std::optional<std::vector<u8>> NesFileParser::read_chr_rom(NesHeader const& header)
{
    std::istream::pos_type offset = header.m_has_trainer ? 512 : 0 + header.m_prg_rom_size * 16384;
    RETURN_BYTES(offset, header.m_chr_rom_size * 8192)
}

int NesFileParser::get()
{
    return m_fs->get();
}

bool NesFileParser::is_eof()
{
    return m_fs->eof();
}
