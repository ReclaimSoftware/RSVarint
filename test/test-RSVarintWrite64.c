#include <RSVarint.h>
#include <RSTest.h>

void test_RSVarintWrite64() {
    DESCRIBE("RSVarintWrite64");

    TEST("2**32 -> 80 80 80 80 10") {
        // 2**32 = 0b100000000000000000000000000000000
        //       = little_endian_128(" 0000000  0000000  0000000  0000000  0010000")
        //       =         varint128("10000000 10000000 10000000 10000000 00010000")
        uint8_t buffer[11] = {3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3};
        uint8_t expected[11] = {3, 0x80, 0x80, 0x80, 0x80, 0x10, 7, 6, 5, 4, 3};
        uint32_t pos = 1;
        RSVarintWrite64((uint64_t)4294967296ull, buffer, &pos);
        assert_data_equal(buffer, expected, 11);
        assert_ints_equal(6, pos);
    }

    TEST("(2**64 - 1) -> FF FF FF FF FF FF FF FF FF 01") {
        // 2**64 - 1
        // = 0b(11111111 11111111 11111111 11111111  11111111 11111111 11111111 11111111)
        // = little_endian_128(" 1111111  1111111  1111111  1111111  1111111  1111111  1111111  1111111  1111111  0000001")
        // =         varint128("11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 00000001")
        uint8_t buffer[11] = {3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3};
        uint8_t expected[11] = {3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};
        uint32_t pos = 1;
        RSVarintWrite64((uint64_t)18446744073709551615ull, buffer, &pos);
        assert_data_equal(buffer, expected, 11);
        assert_ints_equal(11, pos);
    }

    // The following are copypasta'd from the 32-bit version:

    TEST("0 -> 00") {
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0, 5, 6, 7, 8};
        uint32_t pos = 1;
        RSVarintWrite64(0, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(2, pos);
    }

    TEST("1 -> 01") {
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 1, 5, 6, 7, 8};
        uint32_t pos = 1;
        RSVarintWrite64(1, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(2, pos);
    }

    TEST("127 -> 7F") {
        // 127 = 0b1111111 = varint128("01111111")
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0x7F, 5, 6, 7, 8};
        uint32_t pos = 1;
        RSVarintWrite64(127, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(2, pos);
    }

    TEST("128 -> 80 01") {
        // 128 = 0b10000000 = little_endian_128(" 0000000  0000001")
        //                  =         varint128("10000000 00000001")
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0x80, 0x01, 6, 7, 8};
        uint32_t pos = 1;
        RSVarintWrite64(128, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(3, pos);
    }

    TEST("130 -> 82 01") {
        // 130 = 0b10000001 = little_endian_128(" 0000010  0000001")
        //                  =         varint128("10000010 00000001")
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0x82, 0x01, 6, 7, 8};
        uint32_t pos = 1;
        RSVarintWrite64(130, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(3, pos);
    }

    TEST("128**2 -> 80 80 01") {
        // 128**2 = 0b100000000000000 = little_endian_128(" 0000000  0000000  0000001 ")
        //                            =         varint128("10000000 10000000 00000001 ")
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0x80, 0x80, 0x01, 7, 8};
        uint32_t pos = 1;
        RSVarintWrite64(128 * 128, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(4, pos);
    }

    TEST("128**3 -> 80 80 80 01") {
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0x80, 0x80, 0x80, 0x01, 8};
        uint32_t pos = 1;
        RSVarintWrite64(128 * 128 * 128, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(5, pos);
    }

    TEST("128**4 -> 80 80 80 80 01") {
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0x80, 0x80, 0x80, 0x80, 0x01};
        uint32_t pos = 1;
        RSVarintWrite64(128 * 128 * 128 * 128, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(6, pos);
    }

    TEST("300 -> AC 02") {
        // 300 = 0b100101100 = little_endian_128(" 0101100  0000010")
        //                   =         varint128("10101100 00000010")
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0xAC, 0x02, 6, 7, 8};
        uint32_t pos = 1;
        RSVarintWrite64(300, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(3, pos);
    }

    TEST("31415926 -> F6 BC FD 0E") {
        // 31415926 = 0b1110111110101111001110110
        //          = little_endian_128(" 1110110  0111100  1111101  0001110")
        //          =         varint128("11110110 10111100 11111101 00001110")
        //          =         varint128(0xF6BCFD0E)
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0xF6, 0xBC, 0xFD, 0x0E, 8};
        uint32_t pos = 1;
        RSVarintWrite64(31415926, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(5, pos);
    }

    TEST("(2**32 - 2) -> FE FF FF FF 0F") {
        // (2**32 - 2) = 0b11111111111111111111111111111110
        //             = little_endian_128(" 1111110  1111111  1111111  1111111  0001111")
        //             =         varint128("11111110 11111111 11111111 11111111 00001111")
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F};
        uint32_t pos = 1;
        RSVarintWrite64(4294967294, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(6, pos);
    }

    TEST("(2**32 - 1) -> FF FF FF FF 0F") {
        // (2**32 - 1) = 0b11111111111111111111111111111111
        //             = little_endian_128(" 1111111  1111111  1111111  1111111  0001111")
        //             =         varint128("11111111 11111111 11111111 11111111 00001111")
        uint8_t buffer[6] = {3, 4, 5, 6, 7, 8};
        uint8_t expected[6] = {3, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F};
        uint32_t pos = 1;
        RSVarintWrite64(4294967295, buffer, &pos);
        assert_data_equal(buffer, expected, 6);
        assert_ints_equal(6, pos);
    }
}
