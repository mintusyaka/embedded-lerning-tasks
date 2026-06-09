# Екзаменаційні завдання
 
## Модуль 1.1 — C-основи для embedded
 
**Правила:** без AI, без copy-paste з підручника. Час: ~3–4 години.
 
---
 
### Частина 1 — volatile (20 балів)
 
Напиши дві версії функції:
 
```cpp
// Версія A — без volatile
uint32_t wait_for_flag_unsafe(uint32_t* reg, uint32_t bit_mask);
 
// Версія B — з volatile
uint32_t wait_for_flag_safe(volatile uint32_t* reg, uint32_t bit_mask);
```
 
Обидві чекають поки біт `bit_mask` у регістрі `reg` стане `1` і повертають кількість ітерацій.
 
**Завдання:**
1. Реалізувати обидві функції
2. Зібрати з `-O2 -S` і зберегти обидва `.s` файли окремо
3. Написати у коментарі: яка різниця в асемблері і чому
**Критерій:** в асемблері версії B є інструкція читання з пам'яті всередині циклу. У версії A — цикл вироджений або відсутній.
 
---
 
### Частина 2 — const/constexpr/static (25 балів)
 
**Завдання 2.1.** Знайди і виправ всі помилки (їх 4):
 
```cpp
constexpr int BUFFER_SIZE = 64;
const float PI = 3.14159f;
 
int lookup_table[256] = {
    0, 1, 1, 2, 3, 5, 8, 13
};
 
void process() {
    static int call_count;
    const int local_max = 100;
    local_max = 200;
 
    BUFFER_SIZE = 128;
}
 
float getPI() {
    return PI++;
}
```
 
**Завдання 2.2.** Напиши `constexpr` функцію:
 
```cpp
constexpr uint32_t timer_arr(uint32_t pclk_hz,
                              uint32_t psc,
                              uint32_t freq_hz);
```
 
Формула: `ARR = pclk_hz / (psc + 1) / freq_hz - 1`
 
Додай `static_assert` що результат не перевищує `0xFFFF`.
 
**Завдання 2.3.** Поясни у коментарі чому ця функція завжди повертає `1`:
 
```cpp
int getNextId() {
    int counter = 0;
    return ++counter;
}
```
 
---
 
### Частина 3 — Bitwise (30 балів)
 
**Завдання 3.1.** Реалізуй:
 
```cpp
uint32_t set_field(uint32_t reg,
                   uint8_t  bit_pos,
                   uint8_t  bit_width,
                   uint32_t value);
```
 
Записує `value` у поле шириною `bit_width` бітів з позиції `bit_pos`. Не чіпає інші біти.
 
Приклад:
```
reg=0xFFFFFFFF, bit_pos=4, bit_width=3, value=0b101
результат = 0xFFFFFF5F
```
 
**Завдання 3.2.** Опиши через `struct` з bit fields регістр RCC_AHB1ENR (перші 8 біт):
 
```
bit 0: GPIOAEN
bit 1: GPIOBEN
bit 2: GPIOCEN
bit 3: GPIODEN
bit 4: GPIOEEN
bit 5: зарезервовано
bit 6: зарезервовано
bit 7: GPIOHEN
```
 
Загорни у `union` з `uint32_t raw`. Перевір `sizeof == 4` через `static_assert`.
 
**Завдання 3.3.** Без циклів і бібліотек реалізуй:
 
```cpp
uint32_t reverse_bits(uint32_t value);
```
 
---
 
### Частина 4 — Endianness (25 балів)
 
**Завдання 4.1.** Напиши функцію парсингу пакету датчика:
 
```cpp
struct SensorPacket {
    uint16_t device_id;    // bytes [0:1], big-endian
    uint32_t timestamp;    // bytes [2:5], big-endian
    int16_t  temperature;  // bytes [6:7], big-endian, одиниці: 0.01°C
    uint16_t checksum;     // bytes [8:9], big-endian
};
 
bool parse_packet(const uint8_t* buf, size_t len, SensorPacket& out);
```
 
Повертає `false` якщо `len < 10` або checksum не збігається.
Checksum = сума попередніх байтів (молодший байт).
 
**Завдання 4.2.** Напиши `serialize_packet` та перевір round-trip тестом.
 
---
 
### Структура проекту
 
```
module_1_1_exam/
├── CMakeLists.txt
├── src/
│   ├── volatile_test.cpp
│   ├── const_constexpr.cpp
│   ├── bitwise.cpp
│   ├── endianness.cpp   
│   └── include/
│       ├── big_endian_rw.cpp
│       └── big_endian_rw.hpp
├── tests/
│   └── test_all.cpp
└── asm/
    ├── without_volatile.s
    └── with_volatile.s
```
 
---
 
### Оцінювання
 
| Частина | Балів | Мінімум |
|---|---|---|
| 1 — volatile | 20 | 15 |
| 2 — const/constexpr | 25 | 18 |
| 3 — bitwise | 30 | 22 |
| 4 — endianness | 25 | 18 |
| **Разом** | **100** | **73** |
 
---