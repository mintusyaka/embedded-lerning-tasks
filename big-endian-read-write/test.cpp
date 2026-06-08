#include <gtest/gtest.h>
#include "big_endian_rw.hpp"
#include <cstring>

// Test fixture for big-endian read/write operations
class BigEndianReadWriteTest : public ::testing::Test
{
protected:
    static constexpr size_t BUFFER_SIZE = 256;
    uint8_t buffer[BUFFER_SIZE];

    void SetUp() override
    {
        // Initialize buffer with zeros
        std::memset(buffer, 0, BUFFER_SIZE);
    }
};

// ============================================================================
// Tests for uint8_t
// ============================================================================

TEST_F(BigEndianReadWriteTest, Write_Read_UInt8_Zero)
{
    const uint8_t value = 0x00;
    be::write_be<uint8_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x00);
    uint8_t result = be::read_be<uint8_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt8_Max)
{
    const uint8_t value = 0xFF;
    be::write_be<uint8_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0xFF);
    uint8_t result = be::read_be<uint8_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt8_Arbitrary)
{
    const uint8_t value = 0x42;
    be::write_be<uint8_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x42);
    uint8_t result = be::read_be<uint8_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt8_WithOffset)
{
    const uint8_t value = 0xAB;
    be::write_be<uint8_t>(buffer, 5, value);
    EXPECT_EQ(buffer[5], 0xAB);
    uint8_t result = be::read_be<uint8_t>(buffer, 5);
    EXPECT_EQ(result, value);
}

// ============================================================================
// Tests for uint16_t
// ============================================================================

TEST_F(BigEndianReadWriteTest, Write_Read_UInt16_Zero)
{
    const uint16_t value = 0x0000;
    be::write_be<uint16_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x00);
    EXPECT_EQ(buffer[1], 0x00);
    uint16_t result = be::read_be<uint16_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt16_Max)
{
    const uint16_t value = 0xFFFF;
    be::write_be<uint16_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0xFF);
    EXPECT_EQ(buffer[1], 0xFF);
    uint16_t result = be::read_be<uint16_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt16_BasicValue)
{
    const uint16_t value = 0x1234;
    be::write_be<uint16_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x12);
    EXPECT_EQ(buffer[1], 0x34);
    uint16_t result = be::read_be<uint16_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt16_WithOffset)
{
    const uint16_t value = 0xABCD;
    be::write_be<uint16_t>(buffer, 3, value);
    EXPECT_EQ(buffer[3], 0xAB);
    EXPECT_EQ(buffer[4], 0xCD);
    uint16_t result = be::read_be<uint16_t>(buffer, 3);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt16_MultipleValues)
{
    const uint16_t value1 = 0x1111;
    const uint16_t value2 = 0x2222;
    const uint16_t value3 = 0x3333;

    be::write_be<uint16_t>(buffer, 0, value1);
    be::write_be<uint16_t>(buffer, 2, value2);
    be::write_be<uint16_t>(buffer, 4, value3);

    EXPECT_EQ(be::read_be<uint16_t>(buffer, 0), value1);
    EXPECT_EQ(be::read_be<uint16_t>(buffer, 2), value2);
    EXPECT_EQ(be::read_be<uint16_t>(buffer, 4), value3);
}

// ============================================================================
// Tests for uint32_t
// ============================================================================

TEST_F(BigEndianReadWriteTest, Write_Read_UInt32_Zero)
{
    const uint32_t value = 0x00000000;
    be::write_be<uint32_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x00);
    EXPECT_EQ(buffer[1], 0x00);
    EXPECT_EQ(buffer[2], 0x00);
    EXPECT_EQ(buffer[3], 0x00);
    uint32_t result = be::read_be<uint32_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt32_Max)
{
    const uint32_t value = 0xFFFFFFFF;
    be::write_be<uint32_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0xFF);
    EXPECT_EQ(buffer[1], 0xFF);
    EXPECT_EQ(buffer[2], 0xFF);
    EXPECT_EQ(buffer[3], 0xFF);
    uint32_t result = be::read_be<uint32_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt32_BasicValue)
{
    const uint32_t value = 0x12345678;
    be::write_be<uint32_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x12);
    EXPECT_EQ(buffer[1], 0x34);
    EXPECT_EQ(buffer[2], 0x56);
    EXPECT_EQ(buffer[3], 0x78);
    uint32_t result = be::read_be<uint32_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt32_WithOffset)
{
    const uint32_t value = 0xDEADBEEF;
    be::write_be<uint32_t>(buffer, 10, value);
    EXPECT_EQ(buffer[10], 0xDE);
    EXPECT_EQ(buffer[11], 0xAD);
    EXPECT_EQ(buffer[12], 0xBE);
    EXPECT_EQ(buffer[13], 0xEF);
    uint32_t result = be::read_be<uint32_t>(buffer, 10);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt32_MultipleValues)
{
    const uint32_t value1 = 0x11111111;
    const uint32_t value2 = 0x22222222;

    be::write_be<uint32_t>(buffer, 0, value1);
    be::write_be<uint32_t>(buffer, 4, value2);

    EXPECT_EQ(be::read_be<uint32_t>(buffer, 0), value1);
    EXPECT_EQ(be::read_be<uint32_t>(buffer, 4), value2);
}

// ============================================================================
// Tests for uint64_t
// ============================================================================

TEST_F(BigEndianReadWriteTest, Write_Read_UInt64_Zero)
{
    const uint64_t value = 0x0000000000000000ULL;
    be::write_be<uint64_t>(buffer, 0, value);
    for (size_t i = 0; i < 8; ++i)
        EXPECT_EQ(buffer[i], 0x00);
    uint64_t result = be::read_be<uint64_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt64_Max)
{
    const uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    be::write_be<uint64_t>(buffer, 0, value);
    for (size_t i = 0; i < 8; ++i)
        EXPECT_EQ(buffer[i], 0xFF);
    uint64_t result = be::read_be<uint64_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt64_BasicValue)
{
    const uint64_t value = 0x123456789ABCDEF0ULL;
    be::write_be<uint64_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x12);
    EXPECT_EQ(buffer[1], 0x34);
    EXPECT_EQ(buffer[2], 0x56);
    EXPECT_EQ(buffer[3], 0x78);
    EXPECT_EQ(buffer[4], 0x9A);
    EXPECT_EQ(buffer[5], 0xBC);
    EXPECT_EQ(buffer[6], 0xDE);
    EXPECT_EQ(buffer[7], 0xF0);
    uint64_t result = be::read_be<uint64_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt64_WithOffset)
{
    const uint64_t value = 0xFEDCBA9876543210ULL;
    be::write_be<uint64_t>(buffer, 5, value);
    EXPECT_EQ(buffer[5], 0xFE);
    EXPECT_EQ(buffer[6], 0xDC);
    EXPECT_EQ(buffer[7], 0xBA);
    EXPECT_EQ(buffer[8], 0x98);
    EXPECT_EQ(buffer[9], 0x76);
    EXPECT_EQ(buffer[10], 0x54);
    EXPECT_EQ(buffer[11], 0x32);
    EXPECT_EQ(buffer[12], 0x10);
    uint64_t result = be::read_be<uint64_t>(buffer, 5);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, Write_Read_UInt64_MultipleValues)
{
    const uint64_t value1 = 0x1111111111111111ULL;
    const uint64_t value2 = 0x2222222222222222ULL;

    be::write_be<uint64_t>(buffer, 0, value1);
    be::write_be<uint64_t>(buffer, 8, value2);

    EXPECT_EQ(be::read_be<uint64_t>(buffer, 0), value1);
    EXPECT_EQ(be::read_be<uint64_t>(buffer, 8), value2);
}

// ============================================================================
// Cross-type and Mixed Tests
// ============================================================================

TEST_F(BigEndianReadWriteTest, MixedTypes_8_16_32_64)
{
    uint8_t val8 = 0xAB;
    uint16_t val16 = 0xCDEF;
    uint32_t val32 = 0x12345678;
    uint64_t val64 = 0x9ABCDEF012345678ULL;

    be::write_be<uint8_t>(buffer, 0, val8);
    be::write_be<uint16_t>(buffer, 1, val16);
    be::write_be<uint32_t>(buffer, 3, val32);
    be::write_be<uint64_t>(buffer, 7, val64);

    EXPECT_EQ(be::read_be<uint8_t>(buffer, 0), val8);
    EXPECT_EQ(be::read_be<uint16_t>(buffer, 1), val16);
    EXPECT_EQ(be::read_be<uint32_t>(buffer, 3), val32);
    EXPECT_EQ(be::read_be<uint64_t>(buffer, 7), val64);
}

// ============================================================================
// Edge Cases and Special Values
// ============================================================================

TEST_F(BigEndianReadWriteTest, SpecialValue_0x0102_UInt16)
{
    const uint16_t value = 0x0102;
    be::write_be<uint16_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x01);
    EXPECT_EQ(buffer[1], 0x02);
    uint16_t result = be::read_be<uint16_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, SpecialValue_0xFF00_UInt16)
{
    const uint16_t value = 0xFF00;
    be::write_be<uint16_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0xFF);
    EXPECT_EQ(buffer[1], 0x00);
    uint16_t result = be::read_be<uint16_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

TEST_F(BigEndianReadWriteTest, SpecialValue_0x00FF_UInt16)
{
    const uint16_t value = 0x00FF;
    be::write_be<uint16_t>(buffer, 0, value);
    EXPECT_EQ(buffer[0], 0x00);
    EXPECT_EQ(buffer[1], 0xFF);
    uint16_t result = be::read_be<uint16_t>(buffer, 0);
    EXPECT_EQ(result, value);
}

// ============================================================================
// Round-trip tests (write then read)
// ============================================================================

TEST_F(BigEndianReadWriteTest, RoundTrip_Multiple_UInt16_Values)
{
    const uint16_t values[] = {0x0000, 0x0001, 0x00FF, 0x0100, 0x7FFF, 0x8000, 0xFFFF};

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        SetUp(); // Reset buffer
        be::write_be<uint16_t>(buffer, 0, values[i]);
        uint16_t result = be::read_be<uint16_t>(buffer, 0);
        EXPECT_EQ(result, values[i]) << "Failed for value 0x" << std::hex << values[i];
    }
}

TEST_F(BigEndianReadWriteTest, RoundTrip_Multiple_UInt32_Values)
{
    const uint32_t values[] = {0x00000000, 0x00000001, 0x000000FF, 0x00000100,
                               0x0000FFFF, 0x00010000, 0x12345678, 0x7FFFFFFF,
                               0x80000000, 0xFFFFFFFF};

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        SetUp(); // Reset buffer
        be::write_be<uint32_t>(buffer, 0, values[i]);
        uint32_t result = be::read_be<uint32_t>(buffer, 0);
        EXPECT_EQ(result, values[i]) << "Failed for value 0x" << std::hex << values[i];
    }
}

// ============================================================================
// Test for raw byte representation
// ============================================================================

TEST_F(BigEndianReadWriteTest, RawByteRepresentation_UInt32)
{
    // Manually write bytes and read as uint32_t
    buffer[0] = 0x12;
    buffer[1] = 0x34;
    buffer[2] = 0x56;
    buffer[3] = 0x78;

    uint32_t result = be::read_be<uint32_t>(buffer, 0);
    EXPECT_EQ(result, 0x12345678UL);
}

TEST_F(BigEndianReadWriteTest, RawByteRepresentation_UInt64)
{
    // Manually write bytes and read as uint64_t
    buffer[0] = 0x12;
    buffer[1] = 0x34;
    buffer[2] = 0x56;
    buffer[3] = 0x78;
    buffer[4] = 0x9A;
    buffer[5] = 0xBC;
    buffer[6] = 0xDE;
    buffer[7] = 0xF0;

    uint64_t result = be::read_be<uint64_t>(buffer, 0);
    EXPECT_EQ(result, 0x123456789ABCDEF0ULL);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
