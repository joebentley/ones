#pragma once
#include "NesHeader.h"
#include <istream>
#include <memory>
#include <optional>
#include <vector>

class NesFileParser {
public:
    explicit NesFileParser(std::unique_ptr<std::istream> fs)
        : m_fs(std::move(fs))
    {
    }

    bool parse_magic();
    std::optional<NesHeader> parse_header();
    std::optional<std::vector<u8>> read_prg_rom(NesHeader const& header);
    std::optional<std::vector<u8>> read_chr_rom(NesHeader const& header);

private:
    inline int get();
    inline bool is_eof();
    std::unique_ptr<std::istream> m_fs;
};
