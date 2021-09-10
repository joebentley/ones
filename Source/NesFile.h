#pragma once
#include "NesHeader.h"
#include "Types.h"
#include <istream>
#include <memory>
#include <optional>
#include <vector>

// Basic iNES file for now
class NesFile {
public:
    static std::optional<NesFile> try_from_file(std::unique_ptr<std::istream>);

    void print() { m_header.print(); }

private:
    NesHeader m_header;

    std::vector<u8> m_prg_rom;
    std::vector<u8> m_chr_rom;
};
