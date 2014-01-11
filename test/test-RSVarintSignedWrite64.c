#include <RSVarint.h>
#include <string.h>
#include "framework.h"

void test_RSVarintSignedWrite64() {

    SPEC_BEGIN("2147483648 -> 80 80 80 80 10");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x80, 0x80, 0x80, 0x80, 0x10};
    uint32_t pos = 1;
    RSVarintSignedWrite64(2147483648, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(6, pos);
    SPEC_END;

    SPEC_BEGIN("-2147483649 -> 81 80 80 80 10");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x81, 0x80, 0x80, 0x80, 0x10};
    uint32_t pos = 1;
    RSVarintSignedWrite64(-2147483649, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(6, pos);
    SPEC_END;

    // The following are copypasta'd from the 32-bit version:

    SPEC_BEGIN("0 -> 00");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x00, 5, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintSignedWrite64(0, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(2, pos);
    SPEC_END;

    SPEC_BEGIN("-1 -> 01");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x01, 5, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintSignedWrite64(-1, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(2, pos);
    SPEC_END;

    SPEC_BEGIN("1 -> 02");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x02, 5, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintSignedWrite64(1, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(2, pos);
    SPEC_END;

    SPEC_BEGIN("-2 -> 03");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x03, 5, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintSignedWrite64(-2, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(2, pos);
    SPEC_END;

    SPEC_BEGIN("2147483647 -> FE FF FF FF 0F");
    // 2147483647 -> varint128(4294967294) = FE FF FF FF 0F
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    RSVarintSignedWrite64(2147483647, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(6, pos);
    SPEC_END;

    SPEC_BEGIN("-2147483648 -> FF FF FF FF 0F");
    // -2147483648 -> varint128(4294967295) = FF FF FF FF 0F
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    RSVarintSignedWrite64(-2147483648, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(6, pos);
    SPEC_END;
}
