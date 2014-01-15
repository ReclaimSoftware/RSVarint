#include <RSVarint.h>
#include <RSTest.h>

void test_RSVarintSignedFread64() {
    DESCRIBE("RSVarintSignedFread64");
    int64_t value;
    FILE *file;
    int ok;

    IT("reads 0") {
        value = 2;
        file = assert_fopen("fixtures/0.varint", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_ints_equal(value, 0);
        fclose(file);
    }

    IT("reads 0") {
        value = 2;
        file = assert_fopen("fixtures/0.varint", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_ints_equal(value, 0);
        fclose(file);
    }

    IT("reads -1") {
        value = 2;
        file = assert_fopen("fixtures/minus1.signed", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_ints_equal(value, -1);
        fclose(file);
    }

    IT("reads 2147483647") {
        value = 2;
        file = assert_fopen("fixtures/2147483647.signed", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_ints_equal(value, 2147483647);
        fclose(file);
    }

    IT("reads -2147483648") {
        value = 2;
        file = assert_fopen("fixtures/minus2147483648.signed", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_ints_equal(value, -2147483648);
        fclose(file);
    }

    IT("reads 2147483648") {
        value = 2;
        file = assert_fopen("fixtures/2147483648.signed", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_ints_equal(value, 2147483648);
        fclose(file);
    }

    IT("reads -2147483649") {
        value = 2;
        file = assert_fopen("fixtures/minus2147483649.signed", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 1);
        assert_ints_equal(value, -2147483649);
        fclose(file);
    }

    IT("errors if the file pointer is null") {
        ok = RSVarintSignedFread64(NULL, &value);
        assert_ints_equal(ok, 0);
    }

    IT("errors if the file is empty") {
        file = assert_fopen("fixtures/empty_file", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 0);
        fclose(file);
    }

    IT("errors when reading a non-empty incomplete varint") {
        file = assert_fopen("fixtures/128_truncated.varint", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 0);
        fclose(file);
    }

    IT("errors when loading pre-zigzag 2**64") {
        file = assert_fopen("fixtures/largest_uint64_plus_one.varint", "r");
        ok = RSVarintSignedFread64(file, &value);
        assert_ints_equal(ok, 0);
        fclose(file);
    }
}
