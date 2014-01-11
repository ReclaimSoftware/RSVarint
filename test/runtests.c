#include <stdio.h>
#include "framework.h"

void test_RSVarintWrite();
void test_RSVarintWrite64();
void test_RSVarintSignedWrite();
void test_RSVarintSignedWrite64();
void test_RSVarintRead();
void test_RSVarintRead64();
void test_RSVarintSignedRead();
void test_RSVarintSignedRead64();


int main() {
    start_suite();
    test_RSVarintWrite();
    test_RSVarintWrite64();
    test_RSVarintSignedWrite();
    test_RSVarintSignedWrite64();
    test_RSVarintRead();
    test_RSVarintRead64();
    test_RSVarintSignedRead();
    test_RSVarintSignedRead64();
    pass_suite();
    return 0;
}
