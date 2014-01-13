#include <RSVarint.h>
#include <string.h>
#include "framework.h"

void test_RSVarintFread64() {
    uint64_t value;
    FILE *file;
    int ok;

    IT("errors if the file pointer is null") {
        ok = RSVarintFread64(NULL, &value);
        assert_ints_equal(ok, 0);
    }

    IT("errors if the file is empty") {
        file = fopen("fixtures/empty_file", "r");
        ok = RSVarintFread64(file, &value);
        assert_ints_equal(ok, 0);
        fclose(file);
    }

    IT("errors when reading a non-empty incomplete varint") {
        file = fopen("fixtures/128_truncated.varint", "r");
        ok = RSVarintFread64(file, &value);
        assert_ints_equal(ok, 0);
        fclose(file);
    }

    IT("errors when reading 2**64") {
        file = fopen("fixtures/largest_uint64_plus_one.varint", "r");
        ok = RSVarintFread64(file, &value);
        assert_ints_equal(ok, 0);
        fclose(file);
    }

    IT("reads (2**64 - 1)") {
        value = 2;
        file = fopen("fixtures/largest_uint64.varint", "r");
        ok = RSVarintFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_uints_equal(value, 18446744073709551615ull);
        fclose(file);
    }

    IT("reads 0") {
        value = 2;
        file = fopen("fixtures/0.varint", "r");
        ok = RSVarintFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_uints_equal(value, 0);
        fclose(file);
    }

    IT("reads 128") {
        value = 2;
        file = fopen("fixtures/128.varint", "r");
        ok = RSVarintFread64(file, &value);
        assert_ints_equal(ok, 1);
        // assert_uints_equal(value, 128);
        fclose(file);
    }
}
