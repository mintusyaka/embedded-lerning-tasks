#include <cstdint>
#include <gtest/gtest.h>
#include "mock_gpio.hpp"

TEST(MockGPIOTest, DefaultsToAllPinsCleared)
{
    MockGPIO gpio;

    for (std::uint8_t pin = 0; pin < 8; ++pin) {
        EXPECT_FALSE(gpio.read_pin(pin)) << "Pin " << static_cast<int>(pin) << " should be clear by default";
    }
}

TEST(MockGPIOTest, SetPinActivatesOnlyRequestedPin)
{
    MockGPIO gpio;

    gpio.set_pin(3);

    EXPECT_TRUE(gpio.read_pin(3));
    EXPECT_FALSE(gpio.read_pin(0));
    EXPECT_FALSE(gpio.read_pin(1));
    EXPECT_FALSE(gpio.read_pin(2));
    EXPECT_FALSE(gpio.read_pin(4));
    EXPECT_FALSE(gpio.read_pin(5));
}

TEST(MockGPIOTest, ClearPinDeactivatesOnlyRequestedPin)
{
    MockGPIO gpio;

    gpio.set_pin(0);
    gpio.set_pin(1);
    gpio.set_pin(2);
    gpio.clear_pin(1);

    EXPECT_TRUE(gpio.read_pin(0));
    EXPECT_FALSE(gpio.read_pin(1));
    EXPECT_TRUE(gpio.read_pin(2));
}

TEST(MockGPIOTest, ClearPinOnAlreadyClearedPinDoesNotAffectOthers)
{
    MockGPIO gpio;

    gpio.set_pin(7);
    gpio.clear_pin(0);

    EXPECT_TRUE(gpio.read_pin(7));
    EXPECT_FALSE(gpio.read_pin(0));
}
