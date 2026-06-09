#include "static_pool.hpp"
#include "static_pool_test_types.hpp"

#include <gtest/gtest.h>

namespace {

TEST(StaticPoolTest, FullPoolReturnsNullptrOnNextAllocation) {
    StaticPool<int, 1> pool;

    EXPECT_NE(pool.allocate(), nullptr);
    EXPECT_EQ(pool.allocate(), nullptr);
}

TEST(StaticPoolTest, DeallocateAllowsAllocationAgain) {
    StaticPool<int, 1> pool;

    int* first = pool.allocate();
    ASSERT_NE(first, nullptr);

    pool.deallocate(first);

    int* second = pool.allocate();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, first);
}

TEST(StaticPoolTest, DeallocateNullptrIsSafe) {
    StaticPool<int, 1> pool;

    EXPECT_NO_THROW(pool.deallocate(nullptr));
}

TEST(StaticPoolTest, DeallocateForeignPointerIsSafe) {
    StaticPool<int, 1> pool;
    int foreign = 42;

    EXPECT_NO_THROW(pool.deallocate(&foreign));
}

TEST(StaticPoolTest, OwnsReturnsTrueOnlyForOwnedPointers) {
    StaticPool<int, 2> pool;
    int* first = pool.allocate();
    ASSERT_NE(first, nullptr);

    EXPECT_TRUE(pool.owns(first));

    int foreign = 7;
    EXPECT_FALSE(pool.owns(&foreign));

    pool.deallocate(first);
}

TEST(StaticPoolTest, AllocationAndDeallocationTrackObjectLifetime) {
    Tracked::alive = 0;
    StaticPool<Tracked, 2> pool;

    Tracked* first = pool.allocate();
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(Tracked::alive, 1);

    Tracked* second = pool.allocate();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(Tracked::alive, 2);

    pool.deallocate(first);
    EXPECT_EQ(Tracked::alive, 1);

    pool.deallocate(second);
    EXPECT_EQ(Tracked::alive, 0);
}

}  // namespace
