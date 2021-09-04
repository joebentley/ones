#include "NesFile.h"
#include "NesFileParser.h"

std::optional<NesFile> NesFile::try_from_file(std::unique_ptr<std::istream> fs)
{
    NesFileParser parser(std::move(fs));
    NesFile nes_file;

    auto header = parser.parse_header();
    if (!header.has_value())
        return {};

    nes_file.m_header = header.value();

    auto prg = parser.read_prg_rom(nes_file.m_header);
    if (!prg.has_value())
        return {};

    nes_file.m_prg_rom = std::move(prg.value());

    auto chr = parser.read_chr_rom(nes_file.m_header);
    if (!chr.has_value())
        return {};

    nes_file.m_chr_rom = std::move(chr.value());

    return nes_file;
}
