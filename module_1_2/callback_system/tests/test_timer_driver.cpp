#include "timer_driver.hpp"

#include <gtest/gtest.h>

namespace {

int g_call_count = 0;
void* g_last_user_data = nullptr;

void callback_stub(void* user_data) {
    ++g_call_count;
    g_last_user_data = user_data;
}

void reset_callback_state() {
    g_call_count = 0;
    g_last_user_data = nullptr;
}

}  // namespace

TEST(TimerDriverTest, RegistersCallbacksUntilCapacity) {
    timer_driver driver;
    int user_data_1 = 1;
    int user_data_2 = 2;
    int user_data_3 = 3;
    int user_data_4 = 4;

    EXPECT_TRUE(driver.register_callback(callback_stub, &user_data_1));
    EXPECT_TRUE(driver.register_callback(callback_stub, &user_data_2));
    EXPECT_TRUE(driver.register_callback(callback_stub, &user_data_3));
    EXPECT_TRUE(driver.register_callback(callback_stub, &user_data_4));
    EXPECT_FALSE(driver.register_callback(callback_stub, &user_data_4));
}

TEST(TimerDriverTest, RejectsNullCallbackAndInvalidUnregisterIndex) {
    timer_driver driver;

    EXPECT_FALSE(driver.register_callback(nullptr, nullptr));
    EXPECT_FALSE(driver.unregister_callback(4));
}

TEST(TimerDriverTest, UnregisterRemovesCallbackFromTickCycle) {
    timer_driver driver;
    int first = 11;
    int second = 22;

    reset_callback_state();
    EXPECT_TRUE(driver.register_callback(callback_stub, &first));
    EXPECT_TRUE(driver.register_callback(callback_stub, &second));
    EXPECT_TRUE(driver.unregister_callback(0));

    driver.isr_tick();

    EXPECT_EQ(g_call_count, 1);
    EXPECT_EQ(g_last_user_data, &second);
}

TEST(TimerDriverTest, IsrTickInvokesOnlyActiveCallbacks) {
    timer_driver driver;
    int first = 1;
    int second = 2;

    reset_callback_state();
    EXPECT_TRUE(driver.register_callback(callback_stub, &first));
    EXPECT_TRUE(driver.register_callback(callback_stub, &second));

    driver.isr_tick();

    EXPECT_EQ(g_call_count, 2);
    EXPECT_EQ(g_last_user_data, &second);
}
