#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <math.h>
#include <assert.h>


FILE* file_read_open(FILE* file, const char* file_read_open);

FILE* file_write_open(FILE* file, const char* file_write_open);

int file_close(FILE* file);

#endif // FILE_H_