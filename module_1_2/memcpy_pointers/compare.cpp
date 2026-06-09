#include <cstring>
#include <chrono>
#include <cstdio>

#include "memory-management-with-pointers.hpp"

int main() {
    constexpr size_t SIZE = 64 * 1024;  // 64 KB (safe stack size)
    uint8_t src[SIZE];
    uint8_t dst[SIZE];

    // Заповнити src
    for (size_t i = 0; i < SIZE; i++) src[i] = i & 0xFF;

    // ── my_memcpy ────────────────────────────────────────────────
    auto start = std::chrono::high_resolution_clock::now();
    my_memcpy(dst, src, SIZE);
    auto end = std::chrono::high_resolution_clock::now();

    auto my_time = std::chrono::duration_cast<std::chrono::microseconds>
                   (end - start).count();

    // ── stdlib memcpy ────────────────────────────────────────────
    start = std::chrono::high_resolution_clock::now();
    memcpy(dst, src, SIZE);
    end = std::chrono::high_resolution_clock::now();

    auto std_time = std::chrono::duration_cast<std::chrono::microseconds>
                    (end - start).count();

    // ── Результат ────────────────────────────────────────────────
    printf("my_memcpy:  %lld us\n", my_time);
    printf("std memcpy: %lld us\n", std_time);
    printf("ratio:      %.1fx slower\n", (double)my_time / std_time);

    return 0;
}