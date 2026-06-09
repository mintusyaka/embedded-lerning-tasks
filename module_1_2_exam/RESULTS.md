# Результати екзамену — Модуль 1.2

**Дата:** червень 2025  
**Загальний результат:** 90 / 100 ✅

---

## Частина 1 — Memory Layout (11/15)

### Що зроблено правильно
- `DEVICE_ID` — Flash / `.rodata` ✅
- `s_mode` — RAM / `.bss` ✅
- `VERSION[]` — Flash ✅
- `local_buf`, `local_val` — stack ✅
- Пояснення поведінки `getCounter()` через `static` — повне і правильне ✅

### Зауваження

**-1 бал — `g_uptime` секція:**
```cpp
uint32_t g_uptime = 0; // зберігається у RAM .rdata ← неправильно
```
`.rdata` — це read-only секція у Flash. Ініціалізована змінна яку можна змінювати живе у `.data` (RAM).

**-2 бали — `getCounter` секція:**
```cpp
uint32_t getCounter() { // зберігається у RAM .text ← неправильно
```
`.text` — це секція **коду** і вона знаходиться у **Flash**, не в RAM. Машинні інструкції функції живуть у Flash і не копіюються в RAM при виконанні.

**-1 бал — `static count` секція:**
```cpp
static uint32_t count = 0; // зберігається у RAM .data ← неточно
```
Змінна ініціалізована нулем — компілятор розміщує її у `.bss`. Секція `.bss` містить нуль-ініціалізовані дані і не займає місця у Flash — нулі не зберігаються явно, просто виділяється RAM при старті.

### Таблиця правильних відповідей

| Змінна | Секція | Де фізично | Причина |
|---|---|---|---|
| `DEVICE_ID` | `.rodata` | Flash | `const` глобальна |
| `g_uptime` | `.data` | RAM | ініціалізована глобальна |
| `s_mode` | `.bss` | RAM | неініціалізована static |
| `VERSION[]` | `.rodata` | Flash | `const` масив символів |
| `getCounter` код | `.text` | Flash | машинні інструкції |
| `static count` | `.bss` | RAM | static, ініціалізована 0 |
| `local_buf` | stack | RAM | локальна змінна |
| `local_val` | stack | RAM | локальна змінна |

---

## Частина 2.1 — own_stdlib (12/12)

Всі 4 тести зелені. ✅

### Що зроблено правильно
- `my_memcpy` — коректна обробка overlapping буферів через перевірку `d - s` ✅
- `my_memset` — правильне побайтове заповнення, `val` береться як `unsigned char` ✅
- `my_memeq` — повертає `false` при різниці в останньому байті ✅
- `my_strlen` — коректно повертає `0` для порожнього рядка ✅
- Обробка `nullptr` у всіх функціях ✅

### Зауваження
- Відсутній `#pragma once` у `own_stdlib.hpp` — не критично, але варто додати як звичку.

---

## Частина 2.2 — HardwareRegister (13/13)

Всі 4 тести зелені. ✅

### Що зроблено правильно
- `write_field` — класичний read-modify-write через маску ✅
- `read_field` — правильне маскування і зсув результату ✅
- `set_bits` / `clear_bits` — не зачіпають інші біти ✅
- `volatile uint32_t m_reg` — правильно відображає семантику апаратного регістру ✅
- Обов'язковий тест `WriteFieldPreservesOtherBits` проходить ✅

---

## Частина 3 — EventSystem (25/30)

Всі 5 тестів зелені. ✅

### Що зроблено правильно
- Підписка, emit і відписка базово працюють ✅
- Кілька підписників на одну подію — всі викликаються ✅
- `user_ctx` коректно передається у handler ✅
- `emit` на незареєстровану подію — нічого не відбувається ✅
- Максимум 16 підписників без heap ✅

### Зауваження

**-5 балів — handle інвалідація після `unsubscribe`:**

При відписці масив зсувається:
```cpp
for (size_t i = index; i < subscriber_count_ - 1; ++i) {
    subscribers[i] = subscribers[i + 1];
}
```
Це ламає handles всіх підписників після видаленого:

```
subscribe A → handle=1 (index 0)
subscribe B → handle=2 (index 1)
subscribe C → handle=3 (index 2)

unsubscribe(1) → B зсувається на index 0, C на index 1

unsubscribe(2) → видаляє index 1 = C, а не B!
```

Handle 2 тепер вказує на C замість B. Поточні тести не покривають цей сценарій і проходять, але в реальному коді це призводить до видалення неправильного підписника.

**Правильне рішення** — позначати слот як неактивний замість зсуву:
```cpp
struct Subscriber {
    uint32_t event_id;
    Handler  handler;
    void*    user_ctx;
    bool     active = false;  // додати поле
};

bool unsubscribe(uint32_t handle) {
    if (handle == 0 || handle > MAX_SUBSCRIBERS) return false;
    if (!subscribers[handle - 1].active) return false;
    subscribers[handle - 1].active = false;
    return true;
}
```
При такому підході handle завжди відповідає фіксованому індексу і ніколи не інвалідується.

---

## Частина 4 — StaticPool (29/30)

Всі 6 тестів зелені включно з lifetime тестом через `Tracked`. ✅

### Що зроблено правильно
- `alignas(alignof(T))` — правильне вирівнювання пам'яті ✅
- Placement new у `allocate` — конструктор викликається без heap ✅
- Явний деструктор у `deallocate` — `ptr->~T()` ✅
- `owns()` — коректна перевірка через межі `m_storage` ✅
- `deallocate(nullptr)` — безпечна обробка ✅
- `deallocate` з чужим вказівником — безпечна обробка ✅
- `Tracked::alive` коректно зменшується після `deallocate` ✅

### Зауваження

**-1 бал — explicit instantiation обмежує гнучкість:**

Реалізація у `.cpp` вимагає явного перерахування типів:
```cpp
template class StaticPool<int, 1>;
template class StaticPool<int, 2>;
template class StaticPool<Tracked, 2>;
```
Це означає що при додаванні нового типу треба редагувати `static_pool.cpp`. Стандартний підхід для шаблонів — перенести всю реалізацію у `.hpp`:
```cpp
// static_pool.hpp — і оголошення, і реалізація
template<typename T, size_t N>
T* StaticPool<T, N>::allocate() {
    // ...
}
```
Це не помилка, але обмеження яке проявиться при масштабуванні.

---

## Підсумок

| Частина | Максимум | Отримано |
|---|---|---|
| 1 — Memory Layout | 15 | 11 |
| 2.1 — own_stdlib | 12 | 12 |
| 2.2 — HardwareRegister | 13 | 13 |
| 3 — EventSystem | 30 | 25 |
| 4 — StaticPool | 30 | 29 |
| **Разом** | **100** | **90** |

### Що виправити перед наступним модулем
1. `memory_layout.cpp` — виправити коментарі: `.rdata` → `.data` для `g_uptime`, `.text` у Flash а не RAM, `static count` → `.bss`
2. `EventSystem::unsubscribe` — замінити зсув масиву на `active` флаг
3. `StaticPool` — перенести реалізацію у `.hpp` (опціонально)
4. `own_stdlib.hpp` — додати `#pragma once`