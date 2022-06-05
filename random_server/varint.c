#include "varint.h"
#include <stddef.h>
#include <stdio.h>

static const char SEGMENT_BITS = 0x7F;
static const char CONTINUE_BIT = 0x80;

static long long read_common(char* buffer, unsigned char* bytes_read, int max_pos) {
    long long result = 0;
    int pos = 0;
    char* ptr = buffer;
    
    while (1) {
        result |= ((*ptr & SEGMENT_BITS) << pos);

        if (*ptr & CONTINUE_BIT == 0) {
            printf("Breaking\n");
            break;
        }

        pos += 7;
        if (pos >= max_pos) {
            printf("Too large!\n");
            return 0;
        }

        ptr++;
    }

    result |= ((*ptr & SEGMENT_BITS) << pos);
    ptr++;

    if (bytes_read != NULL) {
        *bytes_read = ptr - buffer + 1;
    }

    return result;
}

long long read_varint(char* buffer, unsigned char* bytes_read) {
    printf("Reading varint...\n");
    return read_common(buffer, bytes_read, 32);
}

long long read_varlong(char* buffer, unsigned char* bytes_read) {
    return read_common(buffer, bytes_read, 64);
}