cd .. &&
    bash build.sh && \
    cd test && \
    gcc \
        -std=c99 \
        -o ../build/runtests \
        -isystem ../ \
        ../build/RSVarint.o \
        framework.c \
        test-RSVarintWrite.c \
        test-RSVarintWrite64.c \
        test-RSVarintSignedWrite.c \
        test-RSVarintSignedWrite64.c \
        runtests.c &&
    ../build/runtests
