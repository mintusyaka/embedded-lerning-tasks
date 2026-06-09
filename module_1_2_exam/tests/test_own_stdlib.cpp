#include "own_stdlib.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>

TEST(OwnStdlibTest, MyMemcpyHandlesOverlappingBuffersWhenDstIsAfterSrc) {
    std::array<unsigned char, 5> data = {1, 2, 3, 4, 5};

    my_memcpy(data.data() + 2, data.data(), 3);

    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 1);
    EXPECT_EQ(data[3], 2);
    EXPECT_EQ(data[4], 3);
}

TEST(OwnStdlibTest, MyMemsetFillsWithZeroAndFF) {
    std::array<unsigned char, 4> zero = {9, 9, 9, 9};
    std::array<unsigned char, 4> ff = {0, 0, 0, 0};

    my_memset(zero.data(), 0, zero.size());
    my_memset(ff.data(), 0xFF, ff.size());

    EXPECT_TRUE(std::all_of(zero.begin(), zero.end(), [](unsigned char v) { return v == 0; }));
    EXPECT_TRUE(std::all_of(ff.begin(), ff.end(), [](unsigned char v) { return v == 0xFF; }));
}

TEST(OwnStdlibTest, MyMemeqReturnsFalseWhenOnlyLastByteDiffers) {
    std::array<unsigned char, 4> a = {0x10, 0x20, 0x30, 0x40};
    std::array<unsigned char, 4> b = {0x10, 0x20, 0x30, 0x41};

    EXPECT_FALSE(my_memeq(a.data(), b.data(), a.size()));
    EXPECT_TRUE(my_memeq(a.data(), a.data(), a.size()));
}

TEST(OwnStdlibTest, MyStrlenReturnsZeroForEmptyString) {
    EXPECT_EQ(my_strlen(""), 0u);
}
