#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "assembler.h"
#include "../lib_file_proc/file.h"
#include "../lib_buffer_proc/buffer.h"


int main(void)
{
    FILE* file_read = nullptr;
    file_read = file_read_open(file_read, "default_assembler_code.asm");

    assert(file_read);
    if(!res_checker((ssize_t)file_read))
        return 0;



    size_t file_size = symbols_number(file_read);

    if(!res_checker((ssize_t)file_size))
        return 0;


    char* buffer = buffer_create(file_size, sizeof(char), file_read);

    assert(buffer);

    size_t c_words_num = command_words_num(buffer, file_size + 1);

    FILE* file_write = nullptr;
    file_write = file_write_open(file_write, "machine_code.asm");

    assert(file_write);
    if(!res_checker((ssize_t)file_write))
        return 0;

         // TODO remove buffer
    translator(buffer, c_words_num, file_write, file_size);


    int f_read_res = file_close(file_read);

    if(!res_checker(f_read_res))
        return 0;

    int f_write_cl = file_close(file_write);

    if(!res_checker(f_write_cl))
        return 0;

    free(buffer);
    buffer = nullptr;

    return 0;
}