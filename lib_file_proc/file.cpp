#include <stdio.h>
#include <math.h>
#include <assert.h>


#include "../lib_buffer_proc/buffer.h"
#include "../lib_file_proc/file.h"

FILE* file_read_open(FILE* file, const char* file_read_open)
{
    assert(!file);

    file = fopen(file_read_open,  "r");

    if(file == nullptr)
    {
        fprintf(stderr, "file read couldn't open\n");
        return 0;
    }

    return file;
}


FILE* file_write_open(FILE* file, const char* file_write_open)
{
    assert(!file);

    file = fopen(file_write_open, "w");

    if(file == nullptr)
    {
        fprintf(stderr, "file write couldn't open\n");
        return 0;
    }

    return file;
}


int file_close(FILE* file)
{
    int file_cl_res = fclose(file);

    if(file_cl_res != 0)
    {
        fprintf(stderr, "file close error\n");
        return 0;
    }

    return 1;
}