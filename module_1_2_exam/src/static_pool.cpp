#include "static_pool.hpp"

#include "static_pool_test_types.hpp"

#include <cstddef>
#include <new>

template<typename T, std::size_t N>
T* StaticPool<T, N>::allocate() {
    for (std::size_t i = 0; i < N; ++i) {
        if (!m_used[i]) {
            m_used[i] = true;
            return new (&m_storage[sizeof(T) * i]) T();
        }
    }
    return nullptr;
};

template<typename T, std::size_t N>
void StaticPool<T, N>::deallocate(T* ptr) {
    if (ptr == nullptr) {
        return;
    }

    ptr->~T();
    const std::size_t index = static_cast<std::size_t>(
        (reinterpret_cast<uint8_t*>(ptr) - m_storage) / sizeof(T));
    if (index < N) {
        m_used[index] = false;
    }
};

template<typename T, std::size_t N>
size_t StaticPool<T, N>::available() const {
    size_t count = 0;
    for (std::size_t i = 0; i < N; ++i) {
        if (!m_used[i]) {
            ++count;
        }
    }
    return count;
};

template<typename T, std::size_t N>
bool StaticPool<T, N>::owns(const T* ptr) const {
    const uint8_t* byte_ptr = reinterpret_cast<const uint8_t*>(ptr);
    return byte_ptr >= m_storage && byte_ptr < m_storage + sizeof(T) * N;
};

template class StaticPool<int, 1>;
template class StaticPool<int, 2>;
template class StaticPool<Tracked, 2>;