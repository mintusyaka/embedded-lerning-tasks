#include "mock_gpio.hpp"

MockGPIO::MockGPIO() : m_odr(0) {}

void MockGPIO::set_pin(std::uint8_t pin_n) {
    m_odr |= (1u << pin_n);
}

void MockGPIO::clear_pin(std::uint8_t pin_n) {
    m_odr &= ~(1u << pin_n);
}

bool MockGPIO::read_pin(std::uint8_t pin_n) const {
    return (m_odr & (1u << pin_n)) != 0;
}
