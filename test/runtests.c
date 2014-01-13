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
void test_RSVarintFread64();
void test_RSVarintSignedFread64();
void test_RSVarintBitcoinRead64();


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
    test_RSVarintFread64();
    test_RSVarintSignedFread64();
    test_RSVarintBitcoinRead64();
    pass_suite();
    return 0;
}
