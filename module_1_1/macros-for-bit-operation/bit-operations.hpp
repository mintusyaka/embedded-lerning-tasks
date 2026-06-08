#pragma once

#include <cstdint>

#define READ_BIT(n) (1U << (n))
#define SET_BIT(value, n) ((value) |= READ_BIT(n))
#define CLR_BIT(value, n) ((value) &= ~READ_BIT(n))
#define TOGGLE_BIT(value, n) ((value) ^= READ_BIT(n))