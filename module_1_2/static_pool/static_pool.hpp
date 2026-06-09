#pragma once

#include <new>
#include <cstddef>
#include <cstdint>

template<typename T, std::size_t N>
class StaticPool {
    alignas(alignof(T)) uint8_t m_storage[sizeof(T) * N];
    bool m_used[N];

public:
    T* allocate();
    void deallocate(T* p);
};