#include "ArgParser.h"
#include "NesFile.h"
#include "SDL.h"
#include "fmt/core.h"
#include <cstdio>
#include <fstream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char** argv)
{
    if (argc == 1) {
        ArgParser::print_usage();
        return 1;
    }

    auto optional_parser = ArgParser::try_parse(argc, argv);

    if (!optional_parser.has_value()) {
        // TODO: print usage here
        fmt::print(stderr, "Failed to parse arguments.\n");
        ArgParser::print_usage();
        return 1;
    }

    auto arg_parser = optional_parser.value();
    auto nes_file_path = arg_parser.ines_file();

    if (!nes_file_path.has_value()) {
        fmt::print(stderr, "No file given to open.\n");
        return 1;
    }

    auto fs = std::make_unique<std::ifstream>(nes_file_path.value(), std::ios::binary);
    if (fs->fail()) {
        fmt::print(stderr, "File {} not found.\n", nes_file_path.value());
        return 1;
    }

    auto nes_file = NesFile::try_from_file(std::move(fs));

    if (!nes_file.has_value()) {
        fmt::print(stderr, "Could not read NES file");
        return 1;
    }

    if (arg_parser.should_print_ines_info()) {
        nes_file.value().print();
        return 0;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fmt::print(stderr, "Could not initialise SDL: {}\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "ones",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        fmt::print(stderr, "Could not create window: {}\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q)
                    quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
