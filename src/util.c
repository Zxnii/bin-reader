#include "util.h"

#include <string.h>

string* new_string(char* characters) {
    size_t length = strlen(characters);

    return new_string_length(characters, length);
}

string* new_string_length(char* characters, size_t length) {
    string* str = malloc(sizeof(string));

    str->data = characters;
    str->length = length;

    return str;
}

void free_string(string* str) {
    free(str->data);
    free(str);
}

Endianness get_endianness(void) {
    uint32_t* test = malloc(sizeof(uint32_t));
    *test = 0xbe00001e;

    uint8_t firstByte = (uint8_t)test[0];

    if (firstByte == 0xbe) {
        return BIG_ENDIAN;
    } else {
        return LITTLE_ENDIAN;
    }
}