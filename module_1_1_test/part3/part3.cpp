#include <cstdint>

struct RCC_AHB1ENR {
    uint32_t GPIOAEN : 1;
    uint32_t GPIOBEN : 1;
    uint32_t GPIOCEN : 1;
    uint32_t GPIODEN : 1;
    uint32_t GPIOEEN : 1;
    uint32_t :2;
    uint32_t GPIOHEN : 1;
};

union RCC_AHB1ENR_REG {
    RCC_AHB1ENR bits;
    uint32_t raw;
};

uint32_t set_field(uint32_t reg,
                   uint8_t  bit_pos,
                   uint8_t  bit_width,
                   uint32_t value);

uint32_t reverse_bits(uint32_t value);

int main() {
    RCC_AHB1ENR_REG reg = {0};
    sizeof(reg); // 4 байт

    return 0;
}

uint32_t set_field(uint32_t reg,
                   uint8_t  bit_pos,
                   uint8_t  bit_width,
                   uint32_t value) {
    for(int i = 0; i < bit_width; i++) {
        if(value & (1U << i)) {
            reg |= (1U << (bit_pos + i));
        } else {
            reg &= ~(1U << (bit_pos + i));
        }
    }
    return reg;
}

uint32_t reverse_bits(uint32_t value)
{
    uint32_t reversed = 0;
    for(int i = 0; i < 32; i++) {
        if(value & (1U << i)) {
            reversed |= (1U << (31 - i));
        }
    }
    return reversed;
}
