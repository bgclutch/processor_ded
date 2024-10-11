#ifndef STACK_H_
#define STACK_H_

// FLAGS
//#define DEBUG

#ifdef DEBUG
    #define DEBUG_VAR(...) __VA_ARGS__
    #define ASSERT(...) assert(__VA_ARGS__)
    #define RETURN_ERROR(error_sum) return_error(error_sum, __FILE__, __func__, __LINE__)
    #define STACK_DUMP(stack_data)  stack_dump( stack_data, __FILE__, __func__, __LINE__)
    #define ASSERT_FUNC(...) assert(__VA_ARGS__)
    #define CANARY_MODE
    #define HASH_MODE
#else
    #define DEBUG_VAR(...)
    #define ASSERT(...)
    #define RETURN_ERROR(...)
    #define STACK_DUMP(...)
    #define ASSERT_FUNC(...) __VA_ARGS__
#endif


#ifdef CANARY_MODE
    #define CANARIES(...) __VA_ARGS__
#else
    #define CANARIES(...)
#endif


#ifdef HASH_MODE
    #define HASH(...) __VA_ARGS__
#else
    #define HASH(...)
#endif



#include <stdio.h>
#include <math.h>
#include <stdint.h>

typedef void void_sex;
typedef size_t StackElem_t;


enum Error_Codes
{
    ALL_IS_OK                  = 0x00,
    SMTH_WAS_BROKEN            = 0x01,
    STACK_ARRAY_ADDRESS_IS_BAD = 0x02,
    NEG_CAPACITY               = 0x04,
    WRONG_HASH                 = 0x08,
    STACK_OVERFLOW             = 0x0F,
    FILE_PTR_IS_ZERO           = 0x10,
    EMPTY_STACK                = 0x20,
    POISON_IN_STACK            = 0x40,
    STACK_NOT_REALLOCED        = 0x96,
    //ADD SOME ERRORS CODES
    //realloc error (na podumat')
};

struct Main_Stack_Struct
{
    #ifdef CANARY_MODE
    uint64_t  left_st_canary;
    #endif

    StackElem_t* stack_array;
    size_t              size;
    size_t          capacity;

    #ifdef DEBUG
    FILE*          dump_file;
    #endif
    #ifdef HASH_MODE
    uint64_t     hash_struct;
    #endif
    #ifdef HASH_MODE
    uint64_t     hash_stack;
    #endif
    #ifdef CANARY_MODE
    uint64_t right_st_canary;
    #endif
};


Error_Codes ctor_stack(Main_Stack_Struct *stack_data);
Error_Codes dtor_stack(Main_Stack_Struct *stack_data);


Error_Codes stack_push(Main_Stack_Struct *stack_data, StackElem_t elem);
Error_Codes stack_pop(Main_Stack_Struct *stack_data, StackElem_t *elem);


void_sex stack_dump(Main_Stack_Struct *stack_data, const char* file_name, const char* func_name, size_t line);


size_t realloc_if_up_needed(Main_Stack_Struct stack_data);


size_t realloc_if_down_needed(Main_Stack_Struct stack_data);


int is_struct_addresses_okay(Main_Stack_Struct *stack_data);


size_t stack_is_err(Main_Stack_Struct *stack_data);


void_sex put_stars(FILE* file);


Error_Codes realloc_maker(Main_Stack_Struct *stack_data, size_t new_capacity);


void_sex return_error(size_t err_code, const char* file, const char* func, int line);


//Error_Codes fill_dead_bytes(char* array, size_t size);


Error_Codes put_canaries(Main_Stack_Struct *stack_data);


size_t struct_elem_hash(const void* address, size_t size);


size_t hash_struct_sum(Main_Stack_Struct *stack_data);



#endif //STACK_H