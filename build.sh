mkdir -p build

gcc -std=c99 -O3 -isystem ./ -c RSVarint.c -o build/RSVarint.o && \
    echo 'Built.'
