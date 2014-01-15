export RSTEST="../upstream/RSTest"
export RSTEST_ARGS="-isystem $RSTEST/ $RSTEST/RSTest.c"

cd .. &&
    bash build.sh && \
    cd test && \
    $CC \
        -std=c99 \
        -Wall \
        -o ../build/runtests \
        $RSTEST_ARGS \
        -isystem ../ \
        ../build/RSVarint.o \
        test-RSVarintWrite.c \
        test-RSVarintWrite64.c \
        test-RSVarintSignedWrite.c \
        test-RSVarintSignedWrite64.c \
        test-RSVarintRead.c \
        test-RSVarintRead64.c \
        test-RSVarintSignedRead.c \
        test-RSVarintSignedRead64.c \
        test-RSVarintFread64.c \
        test-RSVarintSignedFread64.c \
        test-RSVarintBitcoinRead64.c \
        runtests.c &&
    ../build/runtests
