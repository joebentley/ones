#pragma once
#include "Types.h"
#include "Vector.h"

// Basic iNES header for now
class NesFile {
public:
private:
    // Header
    u8 m_prg_rom_size; // in 16kB units, == m_prg_rom.length() / 16384
    u8 m_chr_rom_size; // in 8kB units, == m_chr_rom.length() / 8192

    bool m_vertical_mirror; // https://wiki.nesdev.com/w/index.php?title=Mirroring#Nametable_Mirroring
    bool m_has_save;
    bool m_has_trainer;
    bool m_ignore_mirroring;
    u8 m_mapper;

    // Data
    Vector<u8> m_prg_rom;
    Vector<u8> m_chr_rom;
};
