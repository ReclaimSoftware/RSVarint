mkdir -p build

$CC -std=c99 -O3 -Wall -isystem ./ -c RSVarint.c -o build/RSVarint.o && \
    echo 'Built.'
