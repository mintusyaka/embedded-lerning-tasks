    #include <cstdint>
    #include <cstddef>

    namespace be
    {
        template <typename T>
        T read_be(const uint8_t* data, size_t offset);

        template <typename T>
        void write_be(uint8_t* data, size_t offset, T value);
    }