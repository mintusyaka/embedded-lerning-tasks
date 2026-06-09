#include "static_pool.hpp"
#include "static_pool_test_types.hpp"

#include <gtest/gtest.h>

TEST(StaticPoolTest, AllocatesObjectsAndReturnsNonNull) {
    TestValue::constructed = 0;
    TestValue::destroyed = 0;

    StaticPool<TestValue, 2> pool;
    TestValue* first = pool.allocate();

    ASSERT_NE(first, nullptr);
    EXPECT_EQ(TestValue::constructed, 1);
    EXPECT_EQ(first->value, 7);

    TestValue* second = pool.allocate();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(TestValue::constructed, 2);

    pool.deallocate(first);
    pool.deallocate(second);

    EXPECT_EQ(TestValue::destroyed, 2);
}

TEST(StaticPoolTest, ReusesFreedSlotAfterDeallocation) {
    StaticPool<int, 1> pool;

    int* first = pool.allocate();
    ASSERT_NE(first, nullptr);
    *first = 42;

    pool.deallocate(first);

    int* second = pool.allocate();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, first);
    EXPECT_EQ(*second, 0);

    pool.deallocate(second);
}

TEST(StaticPoolTest, ReturnsNullWhenPoolIsOvergrown) {
    StaticPool<int, 1> pool;

    int* first = pool.allocate();
    ASSERT_NE(first, nullptr);

    int* second = pool.allocate();
    EXPECT_EQ(second, nullptr);

    pool.deallocate(first);
}
