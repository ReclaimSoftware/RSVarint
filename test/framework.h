#ifndef __framework_h__
#define __framework_h__


#include <stdint.h>


#define SPEC_BEGIN(x)   {
#define SPEC_END        pass_test();}


void fail(char *message);
void assert_ints_equal(int64_t x, int64_t y);
void assert_uints_equal(uint64_t x, uint64_t y);

void pass_test();
void start_suite();
void pass_suite();


#endif
