#pragma once

struct callback_slot
{
    void (*callback)(void* user_data);
    void* user_data;
    bool active;
};