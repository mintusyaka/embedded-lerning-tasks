#pragma once

#include <cstdint>

struct SYST_CSR_t {
    uint32_t ENABLE : 1;
    uint32_t TICKINT : 1;
    uint32_t CLKSOURCE : 1;
    uint32_t RESERVED : 13;
    uint32_t COUNTFLAG : 1;
    uint32_t : 15; // padding/reserved bits
};