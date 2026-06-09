#pragma once

struct Tracked {
    inline static int alive = 0;

    Tracked() {
        ++alive;
    }

    ~Tracked() {
        --alive;
    }
};
