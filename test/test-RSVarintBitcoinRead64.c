#include <RSVarint.h>
#include <string.h>
#include "framework.h"

void test_RSVarintBitcoinRead64() {

    IT("reads 0") {
        uint8_t data[2] = {0xEE, 0x00};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 2);
        assert_uints_equal(result, 0);
    }

    IT("reads 1") {
        uint8_t data[2] = {0xEE, 0x01};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 2);
        assert_uints_equal(result, 1);
    }

    IT("reads 252") {
        uint8_t data[2] = {0xEE, 0xFC};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 2);
        assert_uints_equal(result, 252);
    }

    IT("reads 253") {
        uint8_t data[4] = {0xEE, 0xFD,   0xFD, 0x00};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 4);
        assert_uints_equal(result, 253);
    }

    IT("reads (2**16 - 1)") {
        uint8_t data[4] = {0xEE, 0xFD,   0xFF, 0xFF};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 4);
        assert_uints_equal(result, 65535);
    }

    IT("reads 2**16") {
        uint8_t data[6] = {0xEE, 0xFE,   0x00, 0x00, 0x01, 0x00};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 6);
        assert_uints_equal(result, 65536);
    }

    IT("reads (2**32 - 1)") {
        uint8_t data[6] = {0xEE, 0xFE,   0xFF, 0xFF, 0xFF, 0xFF};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 6);
        assert_uints_equal(result, 4294967295);
    }

    IT("reads 2**32") {
        uint8_t data[10] = {0xEE, 0xFF,   0x00, 0x00, 0x00, 0x00,   0x01, 0x00, 0x00, 0x00};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 10);
        assert_uints_equal(result, 4294967296);
    }

    IT("reads (2**64 - 1)") {
        uint8_t data[10] = {0xEE, 0xFF,   0xFF, 0xFF, 0xFF, 0xFF,   0xFF, 0xFF, 0xFF, 0xFF};
        uint32_t offset = 1;
        uint64_t result = RSVarintBitcoinRead64(data, &offset);
        assert_uints_equal(offset, 10);
        assert_uints_equal(result, 18446744073709551615ull);
    }
}
