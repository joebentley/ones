#pragma once
#include "NesHeader.h"
#include <array>
#include <memory>
#include <vector>

class Mapper {
public:
    static std::unique_ptr<Mapper> try_from_file(std::unique_ptr<std::istream>);

    virtual bool fill_roms(std::vector<u8> prg_rom, std::vector<u8> chr_rom) = 0;
    virtual u8* get_byte(u16 address) = 0;
    virtual ~Mapper() = default;

    void print() { m_header.print(); }

private:
    NesHeader m_header;
};

class NROMMapper : public Mapper {
public:
    bool fill_roms(std::vector<u8> prg_rom, std::vector<u8> chr_rom) override;
    u8* get_byte(u16 address) override;

private:
    std::array<u8, 0x6000 - 0x401F> m_waste {};
    std::array<u8, 0x4000> m_prg_rom {};
    std::array<u8, 0x2000> m_prg_ram {};
    std::array<u8, 0x2000> m_chr_rom {};
};