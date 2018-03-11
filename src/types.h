//
// File: types.h
//

#ifndef TYPES_FILE_HEADER
#define TYPES_FILE_HEADER

#include <array>
#include <vector>

using address_type = std::array<uint8_t, 4>;
using pool_type = std::vector<address_type>;

#endif // TYPES_FILE_HEADER
