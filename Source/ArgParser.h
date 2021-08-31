#pragma once
#include "Optional.h"
#include "String.h"

class ArgParser {
public:
    static Optional<ArgParser> try_parse(String const& argv);

private:
    Optional<String> m_ines_file {};
    bool m_print_ines_info { false };
};
