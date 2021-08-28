#pragma once

#define NON_COPYABLE(klass)                     \
klass(klass const& other) = delete;             \
klass& operator=(klass const& other) = delete;

#define NON_MOVABLE(klass)                      \
klass(klass&& other) = delete;                  \
klass& operator=(klass&& other) = delete;