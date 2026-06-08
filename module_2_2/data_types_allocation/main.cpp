#include <cstdint>
#include <cstdio>

const std::int32_t global_const_int32 = 42;
std::int32_t global_int32 = 42;

std::int32_t static_local_int32();
std::int32_t local_int32();

int main()
{
    std::printf("global_const_int32: %d %p \n", global_const_int32, (void*)&global_const_int32);
    std::printf("global_int32: %d %p \n", global_int32, (void*)&global_int32);
    static_local_int32();
    
    local_int32();

    static_local_int32();

    return 0;
}

std::int32_t static_local_int32()
{
    static std::int32_t static_local_int32 = 42;
    std::printf("static_local_int32: %d %p \n", static_local_int32, (void*)&static_local_int32);
 
    return static_local_int32++;
}

std::int32_t local_int32()
{
    std::int32_t local_int32 = 42;
    std::printf("local_int32: %d %p \n", local_int32, (void*)&local_int32);

    return local_int32++;
}
