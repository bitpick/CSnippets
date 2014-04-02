
#ifndef TSSERROR_H_
#define TSSERROR_H_

#include <stdint.h>

char* TSS_getError_str( uint32_t err );
char* TSS_getError_desc( uint32_t err );

#endif
