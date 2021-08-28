set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(ones_sources main.cpp)

message(${SDL2_LIBRARIES})
add_executable(ones ${ones_sources})
target_include_directories(ones PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(ones ${SDL2_LIBRARIES} AK)
