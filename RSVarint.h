#ifndef __RSVarint_header__
#define __RSVarint_header__

#include <stdint.h>

void RSVarintWrite(uint32_t n, uint8_t *data, uint32_t *offset);
void RSVarintWrite64(uint64_t n, uint8_t *data, uint32_t *offset);
void RSVarintSignedWrite(int32_t value, uint8_t *data, uint32_t *offset);
void RSVarintSignedWrite64(int64_t value, uint8_t *data, uint32_t *offset);

#endif
