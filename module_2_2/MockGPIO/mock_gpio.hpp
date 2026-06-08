#include <cstdint>

class MockGPIO {
public:
    MockGPIO();

    void set_pin(std::uint8_t pin_n);

    void clear_pin(std::uint8_t pin_n);

    bool read_pin(std::uint8_t pin_n) const;
private:
    volatile std::uint32_t m_odr;
};