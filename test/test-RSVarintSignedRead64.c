#include <RSVarint.h>
#include <RSTest.h>

void test_RSVarintSignedRead64() {
    DESCRIBE("RSVarintSignedRead64");

    TEST("read 2147483648") {
        uint8_t data[6] = {0xEE, 0x80, 0x80, 0x80, 0x80, 0x10};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(2147483648ll, result);
        assert_ints_equal(1 + 5, pos);
    }

    TEST("read -2147483649") {
        uint8_t data[6] = {0xEE, 0x81, 0x80, 0x80, 0x80, 0x10};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(-2147483649ll, result);
        assert_ints_equal(1 + 5, pos);
    }

    // The following are copypasta'd from the 32-bit version:

    TEST("read 0") {
        uint8_t data[2] = {0xEE, 0x00};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(0, result);
        assert_ints_equal(1 + 1, pos);
    }

    TEST("read -1") {
        uint8_t data[2] = {0xEE, 0x01};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(-1, result);
        assert_ints_equal(1 + 1, pos);
    }

    TEST("read 1") {
        uint8_t data[2] = {0xEE, 0x02};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(1, result);
        assert_ints_equal(1 + 1, pos);
    }

    TEST("read -2") {
        uint8_t data[2] = {0xEE, 0x03};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(-2, result);
        assert_ints_equal(1 + 1, pos);
    }

    TEST("read 2147483647") {
        uint8_t data[6] = {0xEE, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(2147483647, result);
        assert_ints_equal(1 + 5, pos);
    }

    TEST("read -2147483648") {
        uint8_t data[6] = {0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F};
        uint32_t pos = 1;
        int64_t result = RSVarintSignedRead64(data, &pos);
        assert_ints_equal(-2147483648, result);
        assert_ints_equal(1 + 5, pos);
    }
}
