cmake_minimum_required(VERSION 3.23.0)

project(bin-reader)

add_library(bin-reader STATIC src/bin_reader.c src/util.c)
target_include_directories(bin-reader PRIVATE src include/bin_reader)