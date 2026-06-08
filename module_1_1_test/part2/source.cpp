constexpr int BUFFER_SIZE = 64;
const float PI = 3.14159f;

int lookup_table[256] = {
    0, 1, 1, 2, 3, 5, 8, 13 // ... fibonacci
}; // погана ідея оголошувати такий великий масив таким чином
// зараз він розміщений у RAM, якщо поставити constexpr - він буде обчислений та збережений у Flash пам'ять, так буде ліпше

void process() {
    static int call_count;
    const int local_max = 100;
    local_max = 200; // не можна змінювати константну змінну

    BUFFER_SIZE = 128; // значення constexpr було обчислено ще на етапі компілції, змінювати його в рантайм не вийде

float getPI() {
    return PI++; // не вийде змінити PI, бо це константна змінна
}

constexpr uint32_t timer_arr(uint32_t pclk_hz,
                              uint32_t psc,
                              uint32_t freq_hz) {
    uint32_t arr = pclk_hz / (psc + 1) / (freq_hz - 1);
    static_assert(arr > 65536, "Timer ARR value exceeds 16-bit limit");
    return arr;
}


int getNextId() {
    int counter = 0;
    return ++counter;
}
// завжди повертатиме 1, бо counter це локальна змінна, вона ініціалізується при виклику функцію у стеку, ++counter додає одиницю, і після return функція завершується та звільняє стек, значення counter не зберігається
