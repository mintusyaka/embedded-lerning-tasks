#include <cstddef>

void* my_memcpy (void* dst, const void* src, size_t n);
void* my_memset (void* dst, int val, size_t n);
bool  my_memeq  (const void* a, const void* b, size_t n);
size_t my_strlen(const char* str);