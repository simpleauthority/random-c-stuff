#ifndef VARINT_H
#define VARINT_H 1

char* write_varint(long long number, char* out, unsigned char* bytes_written);

long long read_varint(char* in, unsigned char* bytes_read);

#endif