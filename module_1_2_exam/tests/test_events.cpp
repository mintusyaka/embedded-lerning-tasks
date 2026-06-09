#include "function_pointers.hpp"

#include <gtest/gtest.h>

namespace {

struct CallState {
    int count = 0;
    uint32_t event_id = 0;
    const void* data = nullptr;
    void* user_ctx = nullptr;
};

struct ContextCapture {
    int count = 0;
    const void* seen_ctx = nullptr;
};

void counting_handler(uint32_t event_id, const void* data, void* user_ctx) {
    auto* state = static_cast<CallState*>(user_ctx);
    ++state->count;
    state->event_id = event_id;
    state->data = data;
}

void capture_ctx_handler(uint32_t, const void*, void* user_ctx) {
    auto* state = static_cast<ContextCapture*>(user_ctx);
    ++state->count;
    state->seen_ctx = user_ctx;
}

}  // namespace

TEST(EventSystemTest, MultipleSubscribersOnSameEventAreAllCalled) {
    EventSystem system;
    CallState first{0, 0, nullptr, nullptr};
    CallState second{0, 0, nullptr, nullptr};

    const uint32_t handle1 = system.subscribe(7, counting_handler, &first);
    const uint32_t handle2 = system.subscribe(7, counting_handler, &second);

    ASSERT_NE(handle1, 0u);
    ASSERT_NE(handle2, 0u);

    system.emit(7, nullptr);

    EXPECT_EQ(first.count, 1);
    EXPECT_EQ(second.count, 1);
    EXPECT_EQ(first.event_id, 7u);
    EXPECT_EQ(second.event_id, 7u);
}

TEST(EventSystemTest, UnsubscribeStopsFurtherCalls) {
    EventSystem system;
    CallState state{0, 0, nullptr, nullptr};

    const uint32_t handle = system.subscribe(5, counting_handler, &state);
    ASSERT_NE(handle, 0u);

    EXPECT_TRUE(system.unsubscribe(handle));
    system.emit(5, nullptr);

    EXPECT_EQ(state.count, 0);
}

TEST(EventSystemTest, SubscribeReturnsZeroWhenCapacityIsFull) {
    EventSystem system;
    CallState state{0, 0, nullptr, nullptr};

    for (uint32_t i = 0; i < MAX_SUBSCRIBERS; ++i) {
        EXPECT_NE(system.subscribe(i, counting_handler, &state), 0u);
    }

    EXPECT_EQ(system.subscribe(999, counting_handler, &state), 0u);
}

TEST(EventSystemTest, UserContextIsPassedToHandler) {
    EventSystem system;
    ContextCapture capture{};

    const uint32_t handle = system.subscribe(3, capture_ctx_handler, &capture);
    ASSERT_NE(handle, 0u);

    system.emit(3, nullptr);

    EXPECT_EQ(capture.count, 1);
    EXPECT_EQ(capture.seen_ctx, &capture);
}

TEST(EventSystemTest, EmitOnUnknownEventDoesNothing) {
    EventSystem system;
    CallState state{0, 0, nullptr, nullptr};

    const uint32_t handle = system.subscribe(1, counting_handler, &state);
    ASSERT_NE(handle, 0u);

    system.emit(99, nullptr);

    EXPECT_EQ(state.count, 0);
}
