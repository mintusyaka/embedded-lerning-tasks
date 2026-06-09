#include "hardware_register.hpp"

#include <gtest/gtest.h>

TEST(HardwareRegisterTest, WriteAndReadStoreTheFullValue) {
    HardwareRegister reg(0x12345678u);

    reg.write(0xA5A5A5A5u);

    EXPECT_EQ(reg.read(), 0xA5A5A5A5u);
}

TEST(HardwareRegisterTest, SetBitsAndClearBitsUpdateOnlyRequestedBits) {
    HardwareRegister reg(0x0u);

    reg.set_bits(0xF0u);
    EXPECT_EQ(reg.read(), 0xF0u);

    reg.clear_bits(0x0Fu);
    EXPECT_EQ(reg.read(), 0xF0u);

    reg.clear_bits(0xF0u);
    EXPECT_EQ(reg.read(), 0x0u);
}

TEST(HardwareRegisterTest, ReadFieldExtractsRequestedBitRange) {
    HardwareRegister reg(0xBEEF1234u);

    EXPECT_EQ(reg.read_field(4, 4), 0x3u);
    EXPECT_EQ(reg.read_field(8, 8), 0x12u);
}

TEST(HardwareRegisterTest, WriteFieldPreservesOtherBits) {
    HardwareRegister reg(0xFFFFFFFFu);

    reg.write_field(4, 4, 0x5u);

    EXPECT_EQ(reg.read(), 0xFFFFFF5Fu);
}
