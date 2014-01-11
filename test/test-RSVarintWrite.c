#include <RSVarint.h>
#include <string.h>
#include "framework.h"

void test_RSVarintWrite() {

    SPEC_BEGIN("0 -> 00");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0, 5, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintWrite(0, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(2, pos);
    SPEC_END;

    SPEC_BEGIN("1 -> 01");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 1, 5, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintWrite(1, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(2, pos);
    SPEC_END;

    SPEC_BEGIN("127 -> 7F");
    // 127 = 0b1111111 = varint128("01111111")
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x7F, 5, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintWrite(127, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(2, pos);
    SPEC_END;

    SPEC_BEGIN("128 -> 80 01");
    // 128 = 0b10000000 = little_endian_128(" 0000000  0000001")
    //                  =         varint128("10000000 00000001")
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x80, 0x01, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintWrite(128, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(3, pos);
    SPEC_END;

    SPEC_BEGIN("130 -> 82 01");
    // 130 = 0b10000001 = little_endian_128(" 0000010  0000001")
    //                  =         varint128("10000010 00000001")
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x82, 0x01, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintWrite(130, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(3, pos);
    SPEC_END;

    SPEC_BEGIN("128**2 -> 80 80 01");
    // 128**2 = 0b100000000000000 = little_endian_128(" 0000000  0000000  0000001 ")
    //                            =         varint128("10000000 10000000 00000001 ")
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x80, 0x80, 0x01, 7, 8};
    uint32_t pos = 1;
    RSVarintWrite(128 * 128, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(4, pos);
    SPEC_END;

    SPEC_BEGIN("128**3 -> 80 80 80 01");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x80, 0x80, 0x80, 0x01, 8};
    uint32_t pos = 1;
    RSVarintWrite(128 * 128 * 128, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(5, pos);
    SPEC_END;

    SPEC_BEGIN("128**4 -> 80 80 80 80 01");
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0x80, 0x80, 0x80, 0x80, 0x01};
    uint32_t pos = 1;
    RSVarintWrite(128 * 128 * 128 * 128, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(6, pos);
    SPEC_END;

    SPEC_BEGIN("300 -> AC 02");
    // 300 = 0b100101100 = little_endian_128(" 0101100  0000010")
    //                   =         varint128("10101100 00000010")
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0xAC, 0x02, 6, 7, 8};
    uint32_t pos = 1;
    RSVarintWrite(300, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(3, pos);
    SPEC_END;

    SPEC_BEGIN("31415926 -> F6 BC FD 0E");
    // 31415926 = 0b1110111110101111001110110
    //          = little_endian_128(" 1110110  0111100  1111101  0001110")
    //          =         varint128("11110110 10111100 11111101 00001110")
    //          =         varint128(0xF6BCFD0E)
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0xF6, 0xBC, 0xFD, 0x0E, 8};
    uint32_t pos = 1;
    RSVarintWrite(31415926, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(5, pos);
    SPEC_END;

    SPEC_BEGIN("(2**32 - 2) -> FE FF FF FF 0F");
    // (2**32 - 2) = 0b11111111111111111111111111111110
    //             = little_endian_128(" 1111110  1111111  1111111  1111111  0001111")
    //             =         varint128("11111110 11111111 11111111 11111111 00001111")
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    RSVarintWrite(4294967294, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(6, pos);
    SPEC_END;

    SPEC_BEGIN("(2**32 - 1) -> FF FF FF FF 0F");
    // (2**32 - 1) = 0b11111111111111111111111111111111
    //             = little_endian_128(" 1111111  1111111  1111111  1111111  0001111")
    //             =         varint128("11111111 11111111 11111111 11111111 00001111")
    uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
    uint8_t expected[6] = {3, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F};
    uint32_t pos = 1;
    RSVarintWrite(4294967295, buffer, &pos);
    assert_ints_equal(0, memcmp(buffer, expected, 6));
    assert_ints_equal(6, pos);
    SPEC_END;
}
