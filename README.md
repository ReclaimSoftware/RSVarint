**Variable-length integer codecs**

[![Build Status](https://secure.travis-ci.org/ReclaimSoftware/RSVarint.png)](http://travis-ci.org/ReclaimSoftware/RSVarint)

All the writing functions increment the offset by the size of the encoded varint.

### [Base 128 Varints](https://developers.google.com/protocol-buffers/docs/encoding#varints)

```c
void RSVarintWrite(uint32_t n, uint8_t *data, uint32_t *offset);
void RSVarintWrite64(uint64_t n, uint8_t *data, uint32_t *offset);
void RSVarintSignedWrite(int32_t value, uint8_t *data, uint32_t *offset);
void RSVarintSignedWrite64(int64_t value, uint8_t *data, uint32_t *offset);
```

### [License: MIT](LICENSE.txt)
