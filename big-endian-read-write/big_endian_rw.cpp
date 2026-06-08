#include "big_endian_rw.hpp"

    namespace be
    {
        template <typename T>
        T read_be(const uint8_t* data, size_t offset)
        {
            static_assert(std::is_integral_v<T>, "T must be an integral type");
            static_assert(sizeof(T) <= sizeof(uint64_t), "T must be at most 64 bits");
            static_assert(std::is_unsigned_v<T>, "T must be an unsigned type");

            T value = 0;
            for (size_t i = 0; i < sizeof(T); ++i)
            {
                value <<= 8;
                value |= data[offset + i];
            }
            return value;
        }

        template <typename T>
        void write_be(uint8_t* data, size_t offset, T value)
        {
            static_assert(std::is_integral_v<T>, "T must be an integral type");
            static_assert(sizeof(T) <= sizeof(uint64_t), "T must be at most 64 bits");
            static_assert(std::is_unsigned_v<T>, "T must be an unsigned type");

            for (size_t i = 0; i < sizeof(T); ++i)
            {
                data[offset + sizeof(T) - 1 - i] = static_cast<uint8_t>(value & 0xFF);
                value >>= 8;
            }
        }
    }