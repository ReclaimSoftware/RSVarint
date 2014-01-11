#include <RSVarint.h>
#include <string.h>
#include "framework.h"

void test_RSVarintRead64() {

    SPEC_BEGIN("read 2**32");
    uint8_t data[6] = {0xEE, 0x80, 0x80, 0x80, 0x80, 0x10};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(4294967296, result);
    assert_ints_equal(1 + 5, pos);
    SPEC_END;

    SPEC_BEGIN("read (2**64 - 1)");
    uint8_t data[11] = {0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(18446744073709551615ull, result);
    assert_ints_equal(1 + 10, pos);
    SPEC_END;

    // The following are copypasta'd from the 32-bit version:

    SPEC_BEGIN("read 0");
    uint8_t data[2] = {0xEE, 0x00};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(0, result);
    assert_ints_equal(1 + 1, pos);
    SPEC_END;

    SPEC_BEGIN("read 1");
    uint8_t data[2] = {0xEE, 0x01};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(1, result);
    assert_ints_equal(1 + 1, pos);
    SPEC_END;

    SPEC_BEGIN("read 127");
    uint8_t data[2] = {0xEE, 0x7F};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(127, result);
    assert_ints_equal(1 + 1, pos);
    SPEC_END;

    SPEC_BEGIN("read 128");
    uint8_t data[3] = {0xEE, 0x80, 0x01};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(128, result);
    assert_ints_equal(1 + 2, pos);
    SPEC_END;

    SPEC_BEGIN("read 130");
    uint8_t data[3] = {0xEE, 0x82, 0x01};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(130, result);
    assert_ints_equal(1 + 2, pos);
    SPEC_END;

    SPEC_BEGIN("read 128**2");
    uint8_t data[4] = {0xEE, 0x80, 0x80, 0x01};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(128 * 128, result);
    assert_ints_equal(1 + 3, pos);
    SPEC_END;

    SPEC_BEGIN("read 128**3");
    uint8_t data[5] = {0xEE, 0x80, 0x80, 0x80, 0x01};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(128 * 128 * 128, result);
    assert_ints_equal(1 + 4, pos);
    SPEC_END;

    SPEC_BEGIN("read 128**4");
    uint8_t data[6] = {0xEE, 0x80, 0x80, 0x80, 0x80, 0x01};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(128 * 128 * 128 * 128, result);
    assert_ints_equal(1 + 5, pos);
    SPEC_END;

    SPEC_BEGIN("read 300");
    uint8_t data[3] = {0xEE, 0xAC, 0x02};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(300, result);
    assert_ints_equal(1 + 2, pos);
    SPEC_END;

    SPEC_BEGIN("read 31415926");
    uint8_t data[5] = {0xEE, 0xF6, 0xBC, 0xFD, 0x0E};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(31415926, result);
    assert_ints_equal(1 + 4, pos);
    SPEC_END;

    SPEC_BEGIN("read (2**32 - 2)");
    uint8_t data[6] = {0xEE, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(4294967294, result);
    assert_ints_equal(1 + 5, pos);
    SPEC_END;

    SPEC_BEGIN("read (2**32 - 1)");
    uint8_t data[6] = {0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    uint64_t result = RSVarintRead64(data, &pos);
    assert_uints_equal(4294967295, result);
    assert_ints_equal(1 + 5, pos);
    SPEC_END;
}
