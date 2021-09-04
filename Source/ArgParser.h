#pragma once
#include <optional>
#include <string>
#include <string_view>
#include <vector>

class ArgParser {
public:
    static std::optional<ArgParser> try_parse(int argc, char** argv);
    static std::optional<ArgParser> try_parse(std::vector<std::string_view> const& argv);

    [[nodiscard]] std::optional<std::string> ines_file() const { return m_ines_file; }
    [[nodiscard]] bool should_print_ines_info() const { return m_print_ines_info; }

    static void print_usage();

private:
    std::optional<std::string>
        m_ines_file {};
    bool m_print_ines_info { false };
};
