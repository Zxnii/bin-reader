#ifndef BIN_READER_H
#define BIN_READER_H

#include "util.h"

typedef struct {
    uint8_t* data;

    size_t offset;
    size_t data_length;

    string* error;

    Endianness endianness;
} BinaryReader;

BinaryReader* new_reader_from_file(char* file);
BinaryReader* new_reader(uint8_t* data, size_t data_length);

void free_reader(BinaryReader* reader);

void reader_seek(BinaryReader* reader, size_t amount);
void* read_bytes(BinaryReader* reader, size_t count);

string* read_string_nt(BinaryReader* reader);

int8_t read_int8(BinaryReader* reader);
uint8_t read_uint8(BinaryReader* reader);

uint16_t read_uint16(BinaryReader* reader, Endianness endianness);
uint16_t read_uint16_be(BinaryReader* reader);
uint16_t read_uint16_le(BinaryReader* reader);

int16_t read_int16(BinaryReader* reader, Endianness endianness);
int16_t read_int16_be(BinaryReader* reader);
int16_t read_int16_le(BinaryReader* reader);

uint32_t read_uint32(BinaryReader* reader, Endianness endianness);
uint32_t read_uint32_be(BinaryReader* reader);
uint32_t read_uint32_le(BinaryReader* reader);

int32_t read_int32(BinaryReader* reader, Endianness endianness);
int32_t read_int32_be(BinaryReader* reader);
int32_t read_int32_le(BinaryReader* reader);

uint64_t read_uint64(BinaryReader* reader, Endianness endianness);
uint64_t read_uint64_be(BinaryReader* reader);
uint64_t read_uint64_le(BinaryReader* reader);

int64_t read_int64(BinaryReader* reader, Endianness endianness);
int64_t read_int64_be(BinaryReader* reader);
int64_t read_int64_le(BinaryReader* reader);

#define GET_AVAIL(reader) (reader->data_length - reader->offset)
#define CHECK_BOUNDS(reader, length) if (GET_AVAIL(reader) < length) { \
    READER_ERROR(reader, "Offset out of range, expected >= 0 and <= %zu. Got: %llu", reader->data_length, reader->offset + length); }
#define READER_ERROR(reader, ...) fprintf(stderr, __VA_ARGS__); exit(1)

#endif