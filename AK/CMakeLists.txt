set(AK_sources
        File.cpp
        Format.cpp
        String.cpp
        Types.h Macros.h)

add_library(AK STATIC ${AK_sources})
target_include_directories(AK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
