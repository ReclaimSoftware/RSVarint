#include <RSVarint.h>


void RSVarintSignedWrite(int32_t value, uint8_t *data, uint32_t *offset) {
  uint32_t zigzagged = (uint32_t)((value << 1) ^ (value >> 31));
  RSVarintWrite(zigzagged, data, offset);
}


void RSVarintSignedWrite64(int64_t value, uint8_t *data, uint32_t *offset) {
  uint64_t zigzagged = (uint64_t)((value << 1) ^ (value >> 63));
  RSVarintWrite64(zigzagged, data, offset);
}


int32_t RSVarintSignedRead(uint8_t *data, uint32_t *offset) {
    uint32_t n = RSVarintRead(data, offset);
    return (n >> 1) ^ -(n & 1);
}


int64_t RSVarintSignedRead64(uint8_t *data, uint32_t *offset) {
    uint64_t n = RSVarintRead64(data, offset);
    return (n >> 1) ^ -(n & 1);
}


int RSVarintSignedFread64(FILE *file, int64_t *value) {
    uint64_t n;
    if (!RSVarintFread64(file, &n)) {
        return 0;
    }
    *value = (n >> 1) ^ -(n & 1);
    return 1;
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


uint32_t RSVarintRead(uint8_t *data, uint32_t *offsetPtr) {
    uint32_t offset = *offsetPtr;
    uint32_t result = 0;
    int shift = 0;
    while (1) {
        result += ((data[offset] & 0x7F) << shift);
        if (data[offset] < 128) {
            *offsetPtr = offset + 1;
            return result;
        }
        offset++;
        shift += 7;
    }
}


uint64_t RSVarintRead64(uint8_t *data, uint32_t *offsetPtr) {
    uint32_t offset = *offsetPtr;
    uint64_t result = 0;
    int shift = 0;
    while (1) {
        result += (((uint64_t)data[offset] & 0x7F) << shift);
        if (data[offset] < 128) {
            *offsetPtr = offset + 1;
            return result;
        }
        offset++;
        shift += 7;
    }
}


int RSVarintFread64(FILE *file, uint64_t *value) {
    if (!file) {
        return 0;
    }
    int c;
    uint64_t result = 0;
    int shift = 0;
    while (1) {
        c = fgetc(file);
        if (c == EOF) {
            return 0;
        }
        if ((shift == (9 * 7)) && (c > 0x01)) {
            // This varint is too large (>= 2**64)
            return 0;
        }

        result += (((uint64_t)c & 0x7F) << shift);
        if (c < 128) {
            if (value) {
                *value = result;
            }
            return 1;
        }
        shift += 7;
    }
}


uint64_t RSVarintBitcoinRead64(uint8_t *data, uint32_t *offset) {
    uint32_t i = *offset;
    uint8_t firstByte = data[i];
    if (firstByte <= 0xFC) {
        *offset = i + 1;
        return firstByte;
    } else if (firstByte == 0xFD) {
        *offset = i + (1 + 2);
        uint16_t *values = (uint16_t *)(&(data[i + 1]));
        return values[0];
    } else if (firstByte == 0xFE) {
        *offset = i + (1 + 4);
        uint32_t *values = (uint32_t *)(&(data[i + 1]));
        return values[0];
    } else {
        *offset = i + (1 + 8);
        uint64_t *values = (uint64_t *)(&(data[i + 1]));
        return values[0];
    }
}
