#ifndef __RSVarint_header__
#define __RSVarint_header__

#include <stdint.h>
#include <stdio.h>

void RSVarintWrite(uint32_t n, uint8_t *data, uint32_t *offset);
void RSVarintWrite64(uint64_t n, uint8_t *data, uint32_t *offset);
void RSVarintSignedWrite(int32_t value, uint8_t *data, uint32_t *offset);
void RSVarintSignedWrite64(int64_t value, uint8_t *data, uint32_t *offset);

uint32_t RSVarintRead(uint8_t *data, uint32_t *offset);
uint64_t RSVarintRead64(uint8_t *data, uint32_t *offset);
int32_t RSVarintSignedRead(uint8_t *data, uint32_t *offset);
int64_t RSVarintSignedRead64(uint8_t *data, uint32_t *offset);

int RSVarintFread64(FILE *file, uint64_t *value);
int RSVarintSignedFread64(FILE *file, int64_t *value);

#endif
