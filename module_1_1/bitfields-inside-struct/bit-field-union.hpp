#include "bit-field-struct.hpp"

union SYST_CSR {
    uint32_t raw;
    SYST_CSR_t bits;
};