#include "static_pool.hpp"

#include "static_pool_test_types.hpp"

template<typename T, std::size_t N>
T* StaticPool<T, N>::allocate() {
    for (std::size_t i = 0; i < N; ++i) {
        if (!m_used[i]) {
            m_used[i] = true;
            return new (&m_storage[sizeof(T) * i]) T();
        }
    }
    return nullptr;
}

template<typename T, std::size_t N>
void StaticPool<T, N>::deallocate(T* p) {
    if (p == nullptr) {
        return;
    }

    p->~T();
    const std::size_t index = static_cast<std::size_t>(
        (reinterpret_cast<uint8_t*>(p) - m_storage) / sizeof(T));
    if (index < N) {
        m_used[index] = false;
    }
}

template class StaticPool<int, 1>;
template class StaticPool<TestValue, 2>;