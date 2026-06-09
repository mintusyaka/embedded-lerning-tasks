#include <cstdint>
#include <cstdio>

const uint32_t    DEVICE_ID   = 0xDEAD; // зберігаєтсья у Flash пам'яті
uint32_t          g_uptime    = 0; // зберігається у RAM .rdata, ініціалізується при завантаженні
static uint8_t    s_mode; // зберігається у RAM .bss, ініціалізується нулями при завантаженні
const char        VERSION[]   = "v1.0.0"; // зберігається у Flash пам'яті, ініціалізується при завантаженні, доступна як рядок

uint32_t getCounter() { // зберігається у RAM .text, ініціалізується при виклику функції
    static uint32_t count = 0; // зберігається у RAM .data, ініціалізується нулями при завантаженні, зберігає своє значення між викликами

    printf("count: %p\n", (void*)&count);

    return ++count;
}
// оскільки локальна змінна count є статичною, вона зберігає значення між викликами функцйії, оскільким зберігається не в стеку і після вивільнення функцією стеку - змінна не стирається
 

int main() {
    uint8_t  local_buf[32]; // RAM stack 
    uint32_t local_val = 42; // RAM stack
    // вивести адреси всіх змінних

    printf("DEVICE_ID: %p\n", (void*)&DEVICE_ID);
    printf("g_uptime: %p\n", (void*)&g_uptime);
    printf("s_mode: %p\n", (void*)&s_mode);
    printf("VERSION: %p\n", (void*)VERSION);
    printf("getCounter: %p\n", (void*)getCounter);
    printf("local_buf: %p\n", (void*)local_buf);
    printf("local_val: %p\n", (void*)&local_val);

    return 0;
}