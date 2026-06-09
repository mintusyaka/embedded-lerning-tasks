#include "hardware_register.hpp"

HardwareRegister::HardwareRegister(uint32_t initial) : m_reg(initial) {}

void HardwareRegister::write(uint32_t value) {
    m_reg = value;
}

uint32_t HardwareRegister::read() const {
    return m_reg;
}

void HardwareRegister::set_bits(uint32_t mask) {
    m_reg |= mask;
}

void HardwareRegister::clear_bits(uint32_t mask) {
    m_reg &= ~mask;
}

uint32_t HardwareRegister::read_field(uint8_t pos, uint8_t width) const {
    const uint32_t mask = ((1u << width) - 1) << pos;
    return (m_reg & mask) >> pos;
}

void HardwareRegister::write_field(uint8_t pos, uint8_t width, uint32_t value) {
    const uint32_t mask = ((1u << width) - 1) << pos;
    m_reg = (m_reg & ~mask) | ((value << pos) & mask);
}