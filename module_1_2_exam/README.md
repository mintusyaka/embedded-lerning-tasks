---
 
## Модуль 1.2 — Вказівники та пам'ять
 
**Правила:** без AI, без copy-paste з підручника. Google Test обов'язковий. CI через GitHub Actions. Час: ~4 години.
 
---
 
### Частина 1 — Memory Layout (15 балів)
 
Напиши програму і для кожної змінної вкажи у коментарі секцію та причину:
 
```cpp
const uint32_t    DEVICE_ID   = 0xDEAD;
uint32_t          g_uptime    = 0;
static uint8_t    s_mode;
const char        VERSION[]   = "v1.0.0";
 
uint32_t getCounter() {
    static uint32_t count = 0;
    return ++count;
}
 
int main() {
    uint8_t  local_buf[32];
    uint32_t local_val = 42;
    // вивести адреси всіх змінних
}
```
 
**Питання:** чому `getCounter()` повертає значення що збільшується при кожному виклику — поясни через memory layout.
 
---
 
### Частина 2 — Вказівники (25 балів)
 
**Завдання 2.1.** Реалізуй без stdlib і покрий тестами:
 
```cpp
void*  my_memcpy (void* dst, const void* src, size_t n);
void*  my_memset (void* dst, int val, size_t n);
bool   my_memeq  (const void* a, const void* b, size_t n);
size_t my_strlen (const char* str);
```
 
Тести обов'язково включають:
- `my_memcpy` з overlapping буферами (`dst > src`)
- `my_memset` з `val=0` і `val=0xFF`
- `my_memeq` де дані різняться лише в останньому байті
- `my_strlen` з порожнім рядком
**Завдання 2.2.** Реалізуй і покрий тестами:
 
```cpp
class HardwareRegister {
public:
    explicit HardwareRegister(uint32_t initial = 0);
 
    void     write(uint32_t value);
    uint32_t read() const;
    void     set_bits(uint32_t mask);
    void     clear_bits(uint32_t mask);
    uint32_t read_field(uint8_t pos, uint8_t width) const;
    void     write_field(uint8_t pos, uint8_t width, uint32_t value);
 
private:
    volatile uint32_t m_reg;
};
```
 
Обов'язковий тест:
 
```cpp
TEST(HardwareRegisterTest, WriteFieldPreservesOtherBits) {
    HardwareRegister reg(0xFFFFFFFF);
    reg.write_field(4, 4, 0x5);
    EXPECT_EQ(reg.read(), 0xFFFFFF5F);
}
```
 
---
 
### Частина 3 — Function Pointers (30 балів)
 
Реалізуй систему обробки подій:
 
```cpp
class EventSystem {
public:
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
    // максимум 16 підписників, без heap
};
```
 
Обов'язкові тести:
- Кілька підписників на одну подію — всі викликаються при `emit`
- `unsubscribe` → підписник більше не викликається
- `subscribe` після заповнення повертає `0`
- `user_ctx` коректно передається у handler
- `emit` на незареєстровану подію — нічого не відбувається
---
 
### Частина 4 — Memory Pool (30 балів)
 
```cpp
template<typename T, size_t N>
class StaticPool {
public:
    T*     allocate();
    void   deallocate(T* ptr);
    size_t available() const;
    bool   owns(const T* ptr) const;
 
private:
    alignas(alignof(T)) uint8_t m_storage[sizeof(T) * N];
    bool m_used[N] = {};
};
```
 
Обов'язкові тести:
- Заповнити повністю → наступний `allocate()` повертає `nullptr`
- `deallocate` → `allocate` → отримуємо валідний вказівник
- `deallocate(nullptr)` — не крашиться
- `deallocate` з чужим вказівником — не крашиться
- `owns()` повертає `true` тільки для своїх вказівників
- Об'єкт конструюється і деструктується коректно (через `Tracked`)
```cpp
struct Tracked {
    static int alive;
    Tracked()  { alive++; }
    ~Tracked() { alive--; }
};
int Tracked::alive = 0;
```
 
---
 
### Структура проекту
 
```
module_1_2_exam/
├── CMakeLists.txt
├── src/
│   ├── memory_layout.cpp
│   ├── hardware_register/
│   │   ├── own_stdlib.hpp
│   │   ├── own_stdlib.cpp
│   │   ├── hardware_register.hpp
│   │   └── hardware_register.cpp
│   ├── event_system/
│   │   ├── function_pointers.hpp
│   │   └── function_pointers.cpp
│   ├── static_pool.hpp
│   └── static_pool.cpp
└── tests/
    ├── test_own_stdlib.cpp
    ├── test_hardware_register.cpp
    ├── test_events.cpp
    └── test_static_pool.cpp
```
 
---
 
### Оцінювання
 
| Частина | Балів | Мінімум |
|---|---|---|
| 1 — Memory Layout | 15 | 10 |
| 2 — Вказівники | 25 | 18 |
| 3 — Function Pointers | 30 | 22 |
| 4 — Memory Pool | 30 | 22 |
| **Разом** | **100** | **72** |
 