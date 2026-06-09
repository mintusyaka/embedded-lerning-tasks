#pragma once

struct TestValue {
    inline static int constructed = 0;
    inline static int destroyed = 0;

    int value = 0;

    explicit TestValue(int v = 7) : value(v) {
        ++constructed;
    }

    ~TestValue() {
        ++destroyed;
    }
};
