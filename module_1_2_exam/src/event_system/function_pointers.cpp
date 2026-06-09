#include "function_pointers.hpp"

EventSystem::EventSystem() : subscriber_count_(0) {}

uint32_t EventSystem::subscribe(uint32_t event_id, Handler handler, void* user_ctx) {
    if (subscriber_count_ >= MAX_SUBSCRIBERS || handler == nullptr) {
        return 0;
    }

    subscribers[subscriber_count_] = {event_id, handler, user_ctx};
    return ++subscriber_count_;
}

bool EventSystem::unsubscribe(uint32_t handle) {
    if (handle == 0 || handle > subscriber_count_) {
        return false;
    }

    const uint32_t index = handle - 1;
    for (size_t i = index; i < subscriber_count_ - 1; ++i) {
        subscribers[i] = subscribers[i + 1];
    }
    --subscriber_count_;
    return true;
}

void EventSystem::emit(uint32_t event_id, const void* data) {
    for (size_t i = 0; i < subscriber_count_; ++i) {
        if (subscribers[i].event_id == event_id) {
            subscribers[i].handler(event_id, data, subscribers[i].user_ctx);
        }
    }
}

size_t EventSystem::subscriber_count(uint32_t event_id) const {
    size_t count = 0;
    for (size_t i = 0; i < subscriber_count_; ++i) {
        if (subscribers[i].event_id == event_id) {
            ++count;
        }
    }
    return count;
}