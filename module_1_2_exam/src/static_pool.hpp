#pragma once

#include <cstddef>
#include <cstdint>

template<typename T, size_t N>
class StaticPool {
public:
    T*     allocate();
    void   deallocate(T* ptr);
    size_t available() const;
    bool   owns(const T* ptr) const;

private:
    alignas(alignof(T)) uint8_t m_storage[sizeof(T) * N];
    bool   m_used[N] = {};
};