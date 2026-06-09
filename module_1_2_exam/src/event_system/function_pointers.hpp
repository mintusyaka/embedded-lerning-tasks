#pragma once

#include <cstdint>
#include <cstddef>

#define MAX_SUBSCRIBERS 16

struct Subscriber {
    uint32_t event_id;
    void(*handler)(uint32_t event_id,
                   const void* data,
                   void* user_ctx);
    void* user_ctx;
};

class EventSystem {
public:
    EventSystem();

    using Handler = void(*)(uint32_t event_id,
                            const void* data,
                            void* user_ctx);

    // Повертає handle (>0) або 0 якщо немає місця
    uint32_t subscribe(uint32_t event_id,
                       Handler handler,
                       void* user_ctx = nullptr);

    // Повертає false якщо handle не знайдено
    bool unsubscribe(uint32_t handle);

    // Викликає всіх підписників на цю подію
    void emit(uint32_t event_id, const void* data = nullptr);

    size_t subscriber_count(uint32_t event_id) const;

private:
    Subscriber subscribers[MAX_SUBSCRIBERS];
    size_t subscriber_count_;
};