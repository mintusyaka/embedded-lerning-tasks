#include "bit-operations.hpp"
#include <cassert>
#include <cstdint>

int main()
{
    uint32_t value = 0;

    assert(READ_BIT(0) == 1U);

    SET_BIT(value, 0);
    assert(value == READ_BIT(0));

    SET_BIT(value, 2);
    assert(value == (READ_BIT(0) | READ_BIT(2)));

    CLR_BIT(value, 0);
    assert(value == READ_BIT(2));

    TOGGLE_BIT(value, 2);
    assert(value == 0U);

    TOGGLE_BIT(value, 3);
    assert(value == READ_BIT(3));

    return 0;
}


