#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


static uint64_t framework_g_num_tests = 0;
static struct timeval t0;
static struct timeval t1;


void fail(char *message) {
    fprintf(stderr, "FAIL: %s\n", message);
    exit(1);
}


void assert_ints_equal(int64_t x, int64_t y) {
    if (x != y) {
        fail("assert_ints_equal");
    }
}


void assert_uints_equal(uint64_t x, uint64_t y) {
    if (x != y) {
        fail("assert_uints_equal");
    }
}


void start_test() {
    framework_g_num_tests++;
}


void start_suite() {
    fprintf(stderr, "Running tests...\n");
    gettimeofday(&t0, NULL);
}


void pass_suite() {
    gettimeofday(&t1, NULL);
    int64_t microseconds = (
        ((t1.tv_sec - t0.tv_sec) * 1000000) +
        (t1.tv_usec - t0.tv_usec)
    );
    fprintf(stderr, "All %lld tests passed in %lld microseconds.\n",
                        (long long)framework_g_num_tests,
                        (long long)microseconds);
}
