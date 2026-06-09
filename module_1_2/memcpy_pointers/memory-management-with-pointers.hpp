#pragma once

#include <cstdint>

void* my_memset(void* dest, int val, std::size_t n);

void* my_memcpy(void* dest, const void* src, std::size_t n);