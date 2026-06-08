#include  <cstdint>

uint32_t wait_for_flag_safe(volatile uint32_t* reg, uint32_t bit_mask) {
    uint32_t iteration_count = 0;
    while ((*reg & bit_mask) == 0) {
        iteration_count++;
    }
    return iteration_count;
}

uint32_t wait_for_flag_unsafe(uint32_t* reg, uint32_t bit_mask) {
    uint32_t iteration_count = 0;
    while ((*reg & bit_mask) == 0) {
        iteration_count++;
    }
    return iteration_count;
}

int main() {
    uint32_t reg = 0;
    uint32_t bit_mask = 0x1;

    // uint32_t count = wait_for_flag_safe(&reg, bit_mask);
    uint32_t count = wait_for_flag_unsafe(&reg, bit_mask);

    return count;
}