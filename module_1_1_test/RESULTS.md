# Результати екзамену — Модуль 1.1

**Дата:** червень 2025  
**Загальний результат:** 85 / 100 ✅

---

## Частина 1 — volatile (18/20)

### Що зроблено правильно
- Обидві функції реалізовані коректно
- Асемблерні файли згенеровані
- Різниця між версіями в асемблері присутня і правильна:
  - `wait_for_flag_safe` — інструкція читання з пам'яті `ldr` присутня у кожній ітерації циклу
  - `wait_for_flag_unsafe` — компілятор оптимізував цикл до нескінченного `jmp`

### Зауваження
- **-2 бали:** обидва `.s` файли однакові — збережено один файл з обома функціями замість двох окремих файлів (один без `volatile`, другий з `volatile`). Мета завдання — порівняти асемблер двох окремих компіляцій.

---

## Частина 2 — const/constexpr/static (16/25)

### Що зроблено правильно
- Знайдено всі 4 помилки у коді:
  - `local_max = 200` — зміна `const` змінної ✅
  - `BUFFER_SIZE = 128` — зміна `constexpr` змінної ✅
  - `PI++` — зміна `const` змінної ✅
  - `lookup_table` без `const` — зайвий RAM ✅
- Пояснення `getNextId` правильне і повне ✅

### Зауваження

**-3 бали — незакрита дужка `process()`:**
```cpp
void process() {
    static int call_count;
    const int local_max = 100;
    local_max = 200;
    BUFFER_SIZE = 128;
              // ← відсутня закриваюча }
float getPI() {   // getPI опинився всередині process()
```
Файл не компілюється через синтаксичну помилку.

**-3 бали — неправильна формула `timer_arr`:**
```cpp
// Написано:
uint32_t arr = pclk_hz / (psc + 1) / (freq_hz - 1);

// Правильно:
uint32_t arr = pclk_hz / (psc + 1) / freq_hz - 1;
```
`freq_hz - 1` та `freq_hz` — різні значення. Ділення має бути на `freq_hz`, а `- 1` віднімається від результату.

**-3 бали — некоректний `static_assert`:**
```cpp
static_assert(arr > 65536, "...");  // умова перевернута
```
Умова `arr > 65536` спрацює коли значення перевищує ліміт — тобто дозволяє неправильні значення. Правильно: `arr <= 0xFFFF`. Також `static_assert` всередині `constexpr` функції не може посилатись на локальну змінну. Правильний підхід:
```cpp
constexpr uint32_t val = timer_arr(42000000, 41, 1000);
static_assert(val <= 0xFFFF, "ARR exceeds 16-bit limit");
```

---

## Частина 3 — Bitwise (28/30)

### Що зроблено правильно
- `set_field` реалізований коректно, всі тести проходять ✅
- `reverse_bits` реалізований коректно, всі тести проходять ✅
- `union RCC_AHB1ENR_REG` з `uint32_t raw` ✅

### Зауваження

**-2 бали — неповна `struct RCC_AHB1ENR`:**

Описано лише 8 біт з 32. Решта 24 біти не оголошені:
```cpp
// Написано — лише 8 біт:
struct RCC_AHB1ENR {
    uint32_t GPIOAEN : 1;
    // ...
    uint32_t GPIOHEN : 1;
    // решта 24 біти відсутні
};

// Правильно — явно закрити всі 32 біти:
struct RCC_AHB1ENR {
    uint32_t GPIOAEN : 1;
    uint32_t GPIOBEN : 1;
    uint32_t GPIOCEN : 1;
    uint32_t GPIODEN : 1;
    uint32_t GPIOEEN : 1;
    uint32_t         : 2;   // зарезервовано [6:5]
    uint32_t GPIOHEN : 1;
    uint32_t         : 24;  // зарезервовано [31:8]
};
```
Без `uint32_t : 24` розмір структури не гарантовано дорівнює 4 байтам на всіх компіляторах. Відсутній `static_assert(sizeof(RCC_AHB1ENR_REG) == 4, "...")`.

---

## Частина 4 — Endianness (23/25)

### Що зроблено правильно
- `read_big_endian` і `write_big_endian` реалізовані коректно ✅
- `parse_packet` коректно перевіряє довжину і checksum ✅
- `serialize_packet` коректно серіалізує і рахує checksum ✅
- Round-trip тест проходить ✅

### Зауваження

**-2 бали — конфлікт `is_unsigned_v` з `int16_t`:**

У `big_endian_rw.cpp` є `static_assert(std::is_unsigned_v<T>)`, але `endianness.cpp` викликає функцію з `int16_t`:
```cpp
int16_t temperature = be::read_be<int16_t>(buf, 6);  // int16_t — signed
```
Це не компілювалось би з оригінальним `big_endian_rw.cpp`. Код працював лише тому що при тестуванні assert було прибрано. Рішення — або видалити `is_unsigned_v` assert, або читати як `uint16_t` з явним кастом:
```cpp
int16_t temperature = static_cast<int16_t>(
    be::read_be<uint16_t>(buf, 6));
```

---

## Підсумок

| Частина | Максимум | Отримано |
|---|---|---|
| 1 — volatile | 20 | 18 |
| 2 — const/constexpr | 25 | 16 |
| 3 — bitwise | 30 | 28 |
| 4 — endianness | 25 | 23 |
| **Разом** | **100** | **85** |

### Що виправити перед наступним модулем
1. `const_constexpr.cpp` — закрити дужку `process()`, виправити формулу `timer_arr`, виправити умову `static_assert`
2. `big_endian_rw.cpp` — прибрати `is_unsigned_v` або додати окремий overload для знакових типів
3. `RCC_AHB1ENR` — додати `uint32_t : 24` та `static_assert` для розміру
4. Генерувати два окремих `.s` файли для порівняння volatile