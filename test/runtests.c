#include <stdio.h>
#include "framework.h"

void test_RSVarintWrite();
void test_RSVarintWrite64();
void test_RSVarintSignedWrite();
void test_RSVarintSignedWrite64();


int main() {
    start_suite();
    test_RSVarintWrite();
    test_RSVarintWrite64();
    test_RSVarintSignedWrite();
    test_RSVarintSignedWrite64();
    pass_suite();
    return 0;
}
