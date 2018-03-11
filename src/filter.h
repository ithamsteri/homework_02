//
// File: filter.h
//

#ifndef FILTER_FILE_HEADER
#define FILTER_FILE_HEADER

#include "output.h"
#include "types.h"

void filter(const pool_type &pool, int n0, int n1 = -1, int n2 = -1,
            int n3 = -1);

void filter_any(const pool_type &pool, int n);

#endif // FILTER_FILE_HEADER
