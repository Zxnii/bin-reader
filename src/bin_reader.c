#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bin_reader.h"
#include "util.h"

BinaryReader* new_reader_from_file(char* file) {
    FILE* fileHandle;

    fopen_s(&fileHandle, file, "rb");

    if (fileHandle == NULL) {
        return NULL;
    }

    fseek(fileHandle, 0L, SEEK_END);

    long fileSize = ftell(fileHandle);

    if (fileSize <= 1L) {
        return NULL;
    }

    rewind(fileHandle);

    uint8_t* fileContents = malloc((size_t) fileSize);

    fread(fileContents, 1, fileSize, fileHandle);
    fclose(fileHandle);

    return new_reader(fileContents, (size_t) fileSize);
}

BinaryReader* new_reader(uint8_t* data, size_t data_length) {
    BinaryReader* reader = malloc(sizeof(BinaryReader));

    reader->data = data;

    reader->offset = 0;
    reader->data_length = data_length;

    reader->endianness = get_endianness();

    return reader;
}

void free_reader(BinaryReader* reader) {
    free(reader->data);
    free(reader);
}

void reader_seek(BinaryReader* reader, size_t amount) {
    reader->offset += amount;

    if (reader->offset < 0) {
        reader->offset = 0;
    } else if (GET_AVAIL(reader) <= 0) {
        reader->offset = reader->data_length;
    }
}

void* read_bytes(BinaryReader* reader, size_t count) {
    CHECK_BOUNDS(reader, count);

    if (count < 1) {
        READER_ERROR(reader, "count must be >= 1, got: %llu", count);
    }

    void* bytes = malloc(count);

    memcpy(bytes, reader->offset + reader->data, count);

    reader_seek(reader, count);

    return bytes;
}

string* read_string(BinaryReader* reader, size_t length) {
    void* bytes = read_bytes(reader, length + 1);

    return new_string_length(bytes, length + 1);
}

string* read_string_nt(BinaryReader* reader) {
    size_t length = 0;

    while (1) {
        CHECK_BOUNDS(reader, 1);

        if (reader->data[reader->offset + length] == 0) {
            break;
        }

        length++;
    }

    void* bytes = read_bytes(reader, length + 1);

    return new_string_length(bytes, length + 1);
}

// i8 readers

uint8_t read_uint8(BinaryReader* reader) {
    CHECK_BOUNDS(reader, 1);

    reader_seek(reader, 1);

    return reader->data[reader->offset - 1];
}

int8_t read_int8(BinaryReader* reader) {
    CHECK_BOUNDS(reader, 1);

    reader_seek(reader, 1);

    return (int8_t) reader->data[reader->offset - 1];
}

// i16 readers

uint16_t read_uint16(BinaryReader* reader, Endianness endianness) {
    CHECK_BOUNDS(reader, 2);

    uint16_t out;

    uint16_t first = read_uint8(reader);
    uint16_t second = read_uint8(reader);

    if (endianness == LITTLE_ENDIAN) {
        out = first | second << 8;
    } else {
        out = second | first << 8;
    }

    return out;
}

uint16_t read_uint16_be(BinaryReader* reader) {
    return read_uint16(reader, BIG_ENDIAN);
}

uint16_t read_uint16_le(BinaryReader* reader) {
    return read_uint16(reader, LITTLE_ENDIAN);
}

int16_t read_int16(BinaryReader* reader, Endianness endianness) {
    CHECK_BOUNDS(reader, 2);

    int16_t out;

    int16_t first = read_uint8(reader);
    int16_t second = read_uint8(reader);

    if (endianness == LITTLE_ENDIAN) {
        out = (int16_t) (first | second << 8);
    } else {
        out = (int16_t) (second | first << 8);
    }

    return out;
}

int16_t read_int16_be(BinaryReader* reader) {
    return read_int16(reader, BIG_ENDIAN);
}

int16_t read_int16_le(BinaryReader* reader) {
    return read_int16(reader, LITTLE_ENDIAN);
}

// i32 readers

uint32_t read_uint32(BinaryReader* reader, Endianness endianness) {
    CHECK_BOUNDS(reader, 4);

    uint32_t out;

    uint32_t first = read_uint16(reader, endianness);
    uint32_t second = read_uint16(reader, endianness);

    if (endianness == LITTLE_ENDIAN) {
        out = first | second << 16;
    } else {
        out = second | first << 16;
    }

    return out;
}

uint32_t read_uint32_be(BinaryReader* reader) {
    return read_uint32(reader, BIG_ENDIAN);
}

uint32_t read_uint32_le(BinaryReader* reader) {
    return read_uint32(reader, LITTLE_ENDIAN);
}

int32_t read_int32(BinaryReader* reader, Endianness endianness) {
    CHECK_BOUNDS(reader, 4);

    int32_t out;

    int32_t first = read_uint16(reader, endianness);
    int32_t second = read_uint16(reader, endianness);

    if (endianness == LITTLE_ENDIAN) {
        out = first | second << 16;
    } else {
        out = second | first << 16;
    }

    return out;
}

int32_t read_int32_be(BinaryReader* reader) {
    return read_int32(reader, BIG_ENDIAN);
}

int32_t read_int32_le(BinaryReader* reader) {
    return read_int32(reader, LITTLE_ENDIAN);
}

// i64 readers

uint64_t read_uint64(BinaryReader* reader, Endianness endianness) {
    CHECK_BOUNDS(reader, 8);

    uint64_t out;

    uint64_t first = read_uint32(reader, endianness);
    uint64_t second = read_uint32(reader, endianness);

    if (endianness == LITTLE_ENDIAN) {
        out = first | second << 32;
    } else {
        out = second | first << 32;
    }

    return out;
}

uint64_t read_uint64_be(BinaryReader* reader) {
    return read_uint64(reader, BIG_ENDIAN);
}

uint64_t read_uint64_le(BinaryReader* reader) {
    return read_uint64(reader, LITTLE_ENDIAN);
}

int64_t read_int64(BinaryReader* reader, Endianness endianness) {
    CHECK_BOUNDS(reader, 8);

    int64_t out;

    int64_t first = read_uint32(reader, endianness);
    int64_t second = read_uint32(reader, endianness);

    if (endianness == LITTLE_ENDIAN) {
        out = first | second << 32;
    } else {
        out = second | first << 32;
    }

    return out;
}

int64_t read_int64_be(BinaryReader* reader) {
    return read_int64(reader, BIG_ENDIAN);
}

int64_t read_int64_le(BinaryReader* reader) {
    return read_int64(reader, LITTLE_ENDIAN);
}
