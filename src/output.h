//
// File: output.h
//

#ifndef OUTPUT_FILE_HEADER
#define OUTPUT_FILE_HEADER

#include "types.h"
#include <ostream>

std::ostream &operator<<(std::ostream &os, const address_type &addr);

#endif // OUTPUT_FILE_HEADER
