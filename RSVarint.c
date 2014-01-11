#include <RSVarint.h>


void RSVarintSignedWrite(int32_t value, uint8_t *data, uint32_t *offset) {
  uint32_t zigzagged = (uint32_t)((value << 1) ^ (value >> 31));
  RSVarintWrite(zigzagged, data, offset);
}


void RSVarintSignedWrite64(int64_t value, uint8_t *data, uint32_t *offset) {
  uint64_t zigzagged = (uint64_t)((value << 1) ^ (value >> 63));
  RSVarintWrite64(zigzagged, data, offset);
}


void RSVarintWrite(uint32_t n, uint8_t *data, uint32_t *offset) {
  int i = *offset;
  data[i] = 0;
  while (n > 0) {
    data[i] = (n & 0x7F);
    n = n >> 7;
    if (n > 0) {
      data[i] = data[i] | 0x80;
      i++;
    }
  }
  i++;
  *offset = i;
}


void RSVarintWrite64(uint64_t n, uint8_t *data, uint32_t *offset) {
  int i = *offset;
  data[i] = 0;
  while (n > 0) {
    data[i] = (n & 0x7F);
    n = n >> 7;
    if (n > 0) {
      data[i] = data[i] | 0x80;
      i++;
    }
  }
  i++;
  *offset = i;
}
