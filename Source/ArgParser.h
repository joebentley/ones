#pragma once
#include <optional>
#include <string>

using std::optional;
using std::string;

class ArgParser {
public:
    static optional<ArgParser> try_parse(string const& argv);

private:
    optional<string> m_ines_file {};
    bool m_print_ines_info { false };
};
