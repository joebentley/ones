set(AK_sources
        ReadonlyFileBuffer.cpp
        Format.cpp
        String.cpp
        Types.h Macros.h Vector.cpp Vector.h Optional.cpp Optional.h StringView.h)

add_library(AK STATIC ${AK_sources})
target_include_directories(AK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
