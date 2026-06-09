#include "memory-management-with-pointers.hpp"

void* my_memset(void* dest, int val, std::size_t n) {
    if(dest == nullptr) {
        return nullptr;
    }

    uint8_t byte = static_cast<uint8_t>(val);
    for (std::size_t i = 0; i < n; ++i) {
        static_cast<uint8_t*>(dest)[i] = byte;
    }
    return dest;
}

void* my_memcpy(void* dest, const void* src, std::size_t n) {
    if(dest == nullptr || src == nullptr) {
        return nullptr;
    }
    auto d = static_cast<uint8_t*>(dest);
    auto s = static_cast<const uint8_t*>(src);

    if(d == s) {
        return dest;
    }

    if(d > s && d - s < n) {
        for (std::size_t i = n; i > 0; --i) {
            d[i - 1] = s[i - 1];
        }
        return dest;
    }

    for (std::size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
    return dest;
}