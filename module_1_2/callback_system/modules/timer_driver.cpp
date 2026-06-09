#include "timer_driver.hpp"

bool timer_driver::register_callback(void (*callback)(void* user_data), void* user_data) {
    if(callback == nullptr) {
        return false;
    }
    
    for (uint8_t i = 0; i < TIMER_DRIVER_SIZE; ++i) {
        if (!m_slots[i].active) {
            m_slots[i].callback = callback;
            m_slots[i].user_data = user_data;
            m_slots[i].active = true;
            return true;
        }
    }
    return false;
}

bool timer_driver::unregister_callback(uint8_t slot_index) {
    if (slot_index >= TIMER_DRIVER_SIZE) {
        return false;
    }
    
    m_slots[slot_index].active = false;
    m_slots[slot_index].callback = nullptr;
    m_slots[slot_index].user_data = nullptr;
    return true;
}

void timer_driver::isr_tick() {
    for (uint8_t i = 0; i < TIMER_DRIVER_SIZE; ++i) {
        if (m_slots[i].active && m_slots[i].callback != nullptr) {
            m_slots[i].callback(m_slots[i].user_data);
        }
    }
}