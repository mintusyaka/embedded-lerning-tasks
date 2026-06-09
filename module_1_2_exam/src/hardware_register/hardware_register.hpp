#pragma once

#include <cstdint>

class HardwareRegister {
public:
    explicit HardwareRegister(uint32_t initial = 0);

    void     write(uint32_t value);
    uint32_t read() const;
    void     set_bits(uint32_t mask);
    void     clear_bits(uint32_t mask);
    uint32_t read_field(uint8_t pos, uint8_t width) const;
    void     write_field(uint8_t pos, uint8_t width, uint32_t value);

private:
    volatile uint32_t m_reg;
};