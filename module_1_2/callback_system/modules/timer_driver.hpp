#pragma once

#include <cstdint>

#include "callback_slot.hpp"

#define TIMER_DRIVER_SIZE 4

class timer_driver {
private:
    callback_slot m_slots[TIMER_DRIVER_SIZE]{};

public:
    timer_driver() = default;
    bool register_callback(void (*callback)(void* user_data), void* user_data);
    bool unregister_callback(uint8_t slot_index);

    void isr_tick();
};