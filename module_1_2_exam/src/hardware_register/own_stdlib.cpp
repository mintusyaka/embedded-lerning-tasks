#include "own_stdlib.hpp"

void* my_memcpy (void* dst, const void* src, size_t n) {
    if(dst == nullptr || src == nullptr) {
        return dst;
    }
    
    auto* d = static_cast<unsigned char*>(dst);
    auto* s = static_cast<const unsigned char*>(src);
    
    if(d - s < static_cast<std::ptrdiff_t>(n) && d - s > 0) {
        // якщо ділянки перекриваються і dst починається після src, копіюємо з кінця
        for (size_t i = n; i > 0; --i) {
            d[i - 1] = s[i - 1];
        }
    }
    else {
        for (size_t i = 0; i < n; ++i) {
            d[i] = s[i];
        }
    }

    return dst;
}

void* my_memset (void* dst, int val, size_t n) {
    if(dst == nullptr) {
        return dst;
    }

    auto* d = static_cast<unsigned char*>(dst);
    auto byte_val = static_cast<unsigned char>(val);
    for (size_t i = 0; i < n; ++i) {
        d[i] = byte_val;
    }

    return dst;
}

bool my_memeq (const void* a, const void* b, size_t n) {
    if(a == nullptr || b == nullptr) {
        return false;
    }

    auto* p1 = static_cast<const unsigned char*>(a);
    auto* p2 = static_cast<const unsigned char*>(b);
    for (size_t i = 0; i < n; ++i) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}

size_t my_strlen(const char* str) {
    if(str == nullptr) {
        return 0;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}