#include <cstdint>

uint8_t wait_flag(volatile uint32_t* reg, uint16_t bit_mask) {
    return ((*reg & bit_mask) != 0) ? 1 : 0;
}

int main() {
    volatile uint32_t* STATUS_REG = (volatile uint32_t*)0x40000000;
    while (!wait_flag(STATUS_REG, 0x01)) {
        // Wait for the bit to be set
    }

    return 0;
}