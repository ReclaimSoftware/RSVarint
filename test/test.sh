cd .. &&
    bash build.sh && \
    cd test && \
    $CC \
        -std=c99 \
        -Wall \
        -o ../build/runtests \
        -isystem ../ \
        ../build/RSVarint.o \
        framework.c \
        test-RSVarintWrite.c \
        test-RSVarintWrite64.c \
        test-RSVarintSignedWrite.c \
        test-RSVarintSignedWrite64.c \
        test-RSVarintRead.c \
        test-RSVarintRead64.c \
        test-RSVarintSignedRead.c \
        test-RSVarintSignedRead64.c \
        runtests.c &&
    ../build/runtests
