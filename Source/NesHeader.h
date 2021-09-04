#pragma once
#include "Types.h"
#include "fmt/core.h"
#include <string>

struct NesHeader {
    u8 m_prg_rom_size; // in 16kB units, == m_prg_rom.length() / 16384
    u8 m_chr_rom_size; // in 8kB units, == m_chr_rom.length() / 8192

    bool m_vertical_mirror; // https://wiki.nesdev.com/w/index.php?title=Mirroring#Nametable_Mirroring
    bool m_has_save;
    bool m_has_trainer;
    bool m_ignore_mirroring;
    u8 m_mapper;
    std::string m_ripper_name;

    // TODO: use fmt::formatter specialisation for this
    void print()
    {
        fmt::print("PRG ROM size: {}*16kB\n", m_prg_rom_size);
        fmt::print("CHR ROM size: {}*8kB\n", m_chr_rom_size);
        fmt::print("Mapper number: {}\n", m_mapper);
        fmt::print("Mirroring: {}\n", m_vertical_mirror ? "vertical" : "horizontal");
        fmt::print("Has save: {}\n", m_has_save ? "yes" : "no");
        fmt::print("Has trainer: {}\n", m_has_trainer ? "yes" : "no");
        fmt::print("Ignore mirroring: {}\n", m_ignore_mirroring ? "yes" : "no");
        if (!m_ripper_name.empty())
            fmt::print("Ripper name: {}\n", m_ripper_name);
    }
};
