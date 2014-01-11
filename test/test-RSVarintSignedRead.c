#include <RSVarint.h>
#include <string.h>
#include "framework.h"

void test_RSVarintSignedRead() {

    SPEC_BEGIN("read 0");
    uint8_t data[2] = {0xEE, 0x00};
    uint32_t pos = 1;
    int32_t result = RSVarintSignedRead(data, &pos);
    assert_ints_equal(0, result);
    assert_ints_equal(1 + 1, pos);
    SPEC_END;

    SPEC_BEGIN("read -1");
    uint8_t data[2] = {0xEE, 0x01};
    uint32_t pos = 1;
    int32_t result = RSVarintSignedRead(data, &pos);
    assert_ints_equal(-1, result);
    assert_ints_equal(1 + 1, pos);
    SPEC_END;

    SPEC_BEGIN("read 1");
    uint8_t data[2] = {0xEE, 0x02};
    uint32_t pos = 1;
    int32_t result = RSVarintSignedRead(data, &pos);
    assert_ints_equal(1, result);
    assert_ints_equal(1 + 1, pos);
    SPEC_END;

    SPEC_BEGIN("read -2");
    uint8_t data[2] = {0xEE, 0x03};
    uint32_t pos = 1;
    int32_t result = RSVarintSignedRead(data, &pos);
    assert_ints_equal(-2, result);
    assert_ints_equal(1 + 1, pos);
    SPEC_END;

    SPEC_BEGIN("read 2147483647");
    uint8_t data[6] = {0xEE, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    int32_t result = RSVarintSignedRead(data, &pos);
    assert_ints_equal(2147483647, result);
    assert_ints_equal(1 + 5, pos);
    SPEC_END;

    SPEC_BEGIN("read -2147483648");
    uint8_t data[6] = {0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    int32_t result = RSVarintSignedRead(data, &pos);
    assert_ints_equal(-2147483648, result);
    assert_ints_equal(1 + 5, pos);
    SPEC_END;
}
