#include <cstdint>

constexpr uint32_t CLOCK_FREQ = 16000000; // 16 MHz
constexpr uint32_t BAUD_RATE = 9600;      // 9600 baud

constexpr uint32_t BAD_BAUD_RATE = 1;      // 9600 baud

constexpr uint32_t uart_brr(uint32_t clk, uint32_t baud) {
    return clk / (16 * baud);
}

int main() {
    constexpr uint32_t brr_value = uart_brr(CLOCK_FREQ, BAUD_RATE);
    static_assert(brr_value <= 65535 && brr_value >= 0, "Calculated BRR value exceeds uint16_t range");
    
    constexpr uint32_t bad_brr_value = uart_brr(CLOCK_FREQ, BAD_BAUD_RATE);
    static_assert(bad_brr_value <= 65535 && bad_brr_value >= 0, "Calculated BRR value exceeds uint16_t range");
    //failed on complile time with static_assert

    return 0;
}