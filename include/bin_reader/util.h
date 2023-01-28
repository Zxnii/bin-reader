#ifndef BIN_READER_UTIL_H
#define BIN_READER_UTIL_H

#include <stdlib.h>
#include <stdint.h>

typedef enum {
    BIG_ENDIAN,
    LITTLE_ENDIAN
} Endianness;

typedef struct {
    char* data;

    size_t length;
} string;

string* new_string(char* characters);
string* new_string_length(char* characters, size_t length);

void free_string(string* str);

Endianness get_endianness(void);

#endif