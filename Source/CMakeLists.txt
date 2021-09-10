set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(ones_sources main.cpp NesFile.cpp NesFile.h ArgParser.cpp ArgParser.h Types.h NesFileParser.cpp NesFileParser.h NesHeader.h Processor.cpp Processor.h Mapper.cpp Mapper.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(ones ${ones_sources})
target_include_directories(ones PUBLIC ${CMAKE_SOURCE_DIR}/Externals/fmt/include)
target_link_libraries(ones ${SDL2_LIBRARIES} ${CMAKE_BINARY_DIR}/Externals/fmt/libfmtd.a)
