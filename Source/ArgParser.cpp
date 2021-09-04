#include "ArgParser.h"
#include "fmt/core.h"
#include <cstdio>

std::optional<ArgParser> ArgParser::try_parse(int argc, char** argv)
{
    // Skip argv[0], which is the program name
    if (argc == 1)
        return {};

    std::vector<std::string_view> string_views;
    for (int i = 1; i < argc; i++) {
        string_views.emplace_back(std::string_view(argv[i]));
    }

    return try_parse(string_views);
}

std::optional<ArgParser> ArgParser::try_parse(std::vector<std::string_view> const& argv)
{
    ArgParser parser;

    for (size_t i = 0; i < argv.size(); i++) {
        if (argv[i] == "--print-ines-info") {
            parser.m_print_ines_info = true;
        } else if (i == argv.size() - 1 && argv[i][0] != '-') {
            parser.m_ines_file.emplace(argv[i]);
        } else {
            fmt::print(stderr, "Unrecognised or misplaced arg: {}", argv[i]);
            return {};
        }
    }

    return parser;
}

void ArgParser::print_usage()
{
    fmt::print("usage: ones [--print-ines-info] <file>\n");
}
