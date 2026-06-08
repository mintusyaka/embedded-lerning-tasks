#include "bit-field-struct.hpp"
#include "bit-field-union.hpp"
#include <gtest/gtest.h>

TEST(BitfieldStruct, BitFieldsWriteAndRead) {
    SYST_CSR reg;
    reg.raw = 0;

    reg.bits.ENABLE = 1;
    reg.bits.TICKINT = 1;
    reg.bits.CLKSOURCE = 1;
    reg.bits.COUNTFLAG = 1;

    EXPECT_EQ(reg.bits.ENABLE, 1u);
    EXPECT_EQ(reg.bits.TICKINT, 1u);
    EXPECT_EQ(reg.bits.CLKSOURCE, 1u);
    EXPECT_EQ(reg.bits.COUNTFLAG, 1u);
}

TEST(BitfieldStruct, RawZeroClearsBits) {
    SYST_CSR reg;
    reg.raw = 0;

    EXPECT_EQ(reg.bits.ENABLE, 0u);
    EXPECT_EQ(reg.bits.TICKINT, 0u);
    EXPECT_EQ(reg.bits.CLKSOURCE, 0u);
    EXPECT_EQ(reg.bits.COUNTFLAG, 0u);
}

TEST(BitfieldStruct, RawAllOnSetsBits) {
    SYST_CSR reg;
    reg.raw = 0xFFFFFFFFu;

    EXPECT_EQ(reg.bits.ENABLE, 1u);
    EXPECT_EQ(reg.bits.TICKINT, 1u);
    EXPECT_EQ(reg.bits.CLKSOURCE, 1u);
    EXPECT_EQ(reg.bits.COUNTFLAG, 1u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
