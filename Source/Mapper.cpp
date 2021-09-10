#include "Mapper.h"
#include "NesFileParser.h"
#include <algorithm>
#include <cassert>
#include <fmt/core.h>

std::unique_ptr<Mapper> Mapper::try_from_file(std::unique_ptr<std::istream> fs)
{
    NesFileParser parser(std::move(fs));
    std::unique_ptr<Mapper> mapper;

    auto header = parser.parse_header();
    if (!header.has_value())
        return {};

    switch (header->m_mapper) {
    case 0:
        mapper = std::make_unique<NROMMapper>();
        break;
    default:
        fmt::print("Mapper not implemented");
        return {};
    }

    mapper->m_header = header.value();

    auto prg = parser.read_prg_rom(mapper->m_header);
    if (!prg.has_value())
        return {};

    auto chr = parser.read_chr_rom(mapper->m_header);
    if (!chr.has_value())
        return {};

    if (!mapper->fill_roms(*prg, *chr))
        return {};

    return mapper;
}

bool NROMMapper::fill_roms(std::vector<u8> prg_rom, std::vector<u8> chr_rom)
{
    if (prg_rom.size() > m_prg_rom.size() || chr_rom.size() > m_chr_rom.size()) {
        fmt::print("NES file rom sizes and mapper's sizes are mismatched.");
        return false;
    }

    std::copy(prg_rom.cbegin(), prg_rom.cend(), m_prg_rom.begin());
    std::copy(chr_rom.cbegin(), chr_rom.cend(), m_chr_rom.begin());

    return true;
}

u8* NROMMapper::get_byte(u16 address)
{
    // Must be in cartridge space
    assert(address >= 0x401F);

    if (address < 0x6000) {
        fmt::print("Access of unmapped area: {:x}.\n", address);
        return &m_waste[address - 0x401F];
    }

    if (address >= 0x6000 && address <= 0x7FFF)
        return &m_prg_ram[address - 0x6000];
    if (address >= 0x8000 && address <= 0xBFFF)
        return &m_prg_rom[address - 0x8000];
    // Mirrors the PRG ROM again
    if (address >= 0xC000)
        return &m_prg_rom[address - 0xC000];

    return nullptr;
}
