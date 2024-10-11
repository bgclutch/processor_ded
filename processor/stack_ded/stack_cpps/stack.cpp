#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>


#include "../stack_headers/stack.h"
#include "../stack_headers/colorised_output.h"


#ifdef CANARY_MODE
    const uint64_t canary_value  = 0x3DB510BA17D4EE; //dumayte podpisatsa

#endif

static const size_t Struct_Ctor_Size =  8;
static const Poison_Byte  = 123456781;
//static StackElem_t Dead_Byte = '№';
static_assert(sizeof(StackElem_t) == 8);


Error_Codes ctor_stack(Main_Stack_Struct *stack_data)
{
    ASSERT(stack_data && "huy tebe a ne stack");

    stack_data->stack_array = (StackElem_t*) calloc(Struct_Ctor_Size * sizeof(StackElem_t) CANARIES( +
                                                    2 * sizeof(canary_value)), sizeof(char));

    if(stack_data->stack_array == nullptr)
        return STACK_ARRAY_ADDRESS_IS_BAD;

    stack_data->capacity = Struct_Ctor_Size;
    stack_data->size     = 0;


    CANARIES
    (stack_data->left_st_canary  = canary_value;
     stack_data->right_st_canary = canary_value;)


    memset(stack_data->stack_array CANARIES(+ sizeof(canary_value)), Poison_Byte, stack_data->capacity);

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    CANARIES(ASSERT_FUNC(DEBUG_VAR(!)put_canaries(stack_data))); // TODO macro ASSERT_FUNC

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    RETURN_ERROR(stack_is_err(stack_data));
    STACK_DUMP(stack_data);
    return ALL_IS_OK;
}

Error_Codes dtor_stack(Main_Stack_Struct *stack_data)
{
    RETURN_ERROR(stack_is_err(stack_data));
    STACK_DUMP(stack_data);

    if(!is_struct_addresses_okay(stack_data))
        return STACK_ARRAY_ADDRESS_IS_BAD;

    memset(stack_data->stack_array CANARIES(+ sizeof(canary_value)), Poison_Byte, stack_data->capacity);

    stack_data->size = 0;
    stack_data->capacity = Struct_Ctor_Size;

    free(stack_data->stack_array);
    stack_data->stack_array = nullptr;
    stack_data = nullptr;

    return ALL_IS_OK;
}


Error_Codes stack_push(Main_Stack_Struct *stack_data, StackElem_t elem)
{
    RETURN_ERROR(stack_is_err(stack_data));

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    Error_Codes realloc_code = realloc_maker(stack_data, realloc_if_up_needed(*stack_data));

    if(realloc_code == STACK_NOT_REALLOCED)
        return realloc_code;

    ASSERT(!realloc_code && "realloc error");

    stack_data->stack_array[CANARIES(sizeof(canary_value)) + stack_data->size++] = elem;

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    RETURN_ERROR(stack_is_err(stack_data));
    STACK_DUMP(stack_data);
    return ALL_IS_OK;
}

Error_Codes stack_pop(Main_Stack_Struct *stack_data, StackElem_t *elem)
{
    ASSERT(elem);

    RETURN_ERROR(stack_is_err(stack_data));

    if(stack_data->size == 0)
    {
        return EMPTY_STACK;
    }


    *elem = stack_data->stack_array[CANARIES(sizeof(canary_value)) + (--stack_data->size)];

    #ifndef DEBUG
        fprintf(stderr, "%c\n", *elem);
    #endif

    DEBUG_VAR
    (put_stars(stack_data->dump_file);
     fprintf(stack_data->dump_file, "popped elem '%c'\n", *elem);)

    stack_data->stack_array[CANARIES(sizeof(canary_value)) + stack_data->size] = Poison_Byte;

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    Error_Codes realloc_code = realloc_maker(stack_data, realloc_if_down_needed(*stack_data));

    if(realloc_code == STACK_NOT_REALLOCED)
        return realloc_code;

    ASSERT(!realloc_code && "realloc error");

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    RETURN_ERROR(stack_is_err(stack_data));
    STACK_DUMP(stack_data);
    return ALL_IS_OK;
}

#ifdef DEBUG
void_sex stack_dump(Main_Stack_Struct *stack_data, const char* file_name, const char* func_name, size_t line) //add checks
{
    RETURN_ERROR(stack_is_err(stack_data));

    put_stars(stack_data->dump_file);
    fprintf  (stack_data->dump_file, "%s %s:%lu\n", file_name, func_name, line);
    put_stars(stack_data->dump_file);

    CANARIES(
    fprintf(stack_data->dump_file, "left struct canary: 0x%0lx\n",      stack_data->left_st_canary);
    fprintf(stack_data->dump_file, "left struct canary address: %p\n", &stack_data->left_st_canary);
    put_stars(stack_data->dump_file);)

    fprintf  (stack_data->dump_file, "stack size: %zu\n",                stack_data->size);
    fprintf  (stack_data->dump_file, "stack size address: %p\n",       &(stack_data->size));
    put_stars(stack_data->dump_file);

    fprintf  (stack_data->dump_file, "stack capacity: %zu\n",            stack_data->capacity);
    fprintf  (stack_data->dump_file, "stack capacity address: %p\n",   &(stack_data->capacity));
    put_stars(stack_data->dump_file);

    fprintf  (stack_data->dump_file, "stack address begin: %p\n",       stack_data->stack_array);
    fprintf  (stack_data->dump_file, "stack address end: %p\n",        &stack_data->stack_array[stack_data->capacity CANARIES(+ 2 *sizeof(canary_value))]);
    put_stars(stack_data->dump_file);

    CANARIES(
    fprintf(stack_data->dump_file, "left stack canary: 0x%0lx\n",   *(uint64_t*)(stack_data->stack_array));
    fprintf(stack_data->dump_file, "left stack canary address: %p\n\n",          stack_data->stack_array);)

    for(size_t i = 0; i < stack_data->size; i++) // printing NON empty element
    {
        fprintf(stack_data->dump_file, "stack element non empty %zu: %c\n",           i,   stack_data->stack_array[i CANARIES(+ sizeof(canary_value))]);
        fprintf(stack_data->dump_file, "stack element non empty %zu address: %p\n\n", i, &(stack_data->stack_array[i CANARIES(+ sizeof(canary_value))]));
    }

    for(size_t i = stack_data->size; i < stack_data->capacity; i++) // printing empty element
    {
        fprintf(stack_data->dump_file, "stack element empty %zu: %c\n",           i,       stack_data->stack_array[i CANARIES(+ sizeof(canary_value))]);
        fprintf(stack_data->dump_file, "stack element empty %zu address: %p\n\n", i,     &(stack_data->stack_array[i CANARIES(+ sizeof(canary_value))]));
    }

    CANARIES(
    fprintf(stack_data->dump_file, "right stack canary: 0x%0lx\n", *(uint64_t*)(stack_data->stack_array  CANARIES(+ sizeof(canary_value)) + stack_data->capacity));
    fprintf(stack_data->dump_file, "right stack canary address: %p\n",          stack_data->stack_array  CANARIES(+ sizeof(canary_value)) + stack_data->capacity);
    put_stars(stack_data->dump_file);)

    HASH(
    fprintf(stack_data->dump_file, "struct hash value: 0x%0lx\n",        stack_data->hash_struct);
    fprintf(stack_data->dump_file, "struct hash address: %p\n",         &stack_data->hash_struct);
    put_stars(stack_data->dump_file);)

    CANARIES(
    fprintf(stack_data->dump_file, "right struct canary: 0x%0lx\n",      stack_data->right_st_canary);
    fprintf(stack_data->dump_file, "right struct canary address: %p\n", &stack_data->right_st_canary);
    put_stars(stack_data->dump_file);)
    put_stars(stack_data->dump_file);


    fprintf(stack_data->dump_file, "\n\n\n\n");
    //printf every address meaning etc

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    RETURN_ERROR(stack_is_err(stack_data));
}
#endif

#ifdef DEBUG
size_t stack_is_err(Main_Stack_Struct *stack_data)
{
    size_t errors_sum = 0;
    if(!is_struct_addresses_okay(stack_data))      return STACK_ARRAY_ADDRESS_IS_BAD;

    HASH(size_t my_hash = hash_struct_sum(stack_data);)
    HASH(size_t stack_hash = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                              CANARIES(+ 2 * sizeof(canary_value)));)

    if(stack_data->capacity <= 0)                  errors_sum += NEG_CAPACITY;
    HASH(if(stack_data->hash_struct != my_hash)    errors_sum += WRONG_HASH;)
    HASH(if(stack_data->hash_stack  != stack_hash) errors_sum += WRONG_HASH;)
    if(stack_data->size > stack_data->capacity)    errors_sum += STACK_OVERFLOW;
    if(stack_data->dump_file == nullptr)           errors_sum += FILE_PTR_IS_ZERO;

    for(size_t i = 0; i < stack_data->size; i++)
        if(stack_data->stack_array[i] == Poison_Byte) errors_sum += 0x40;

    return errors_sum;
}
#endif


Error_Codes realloc_maker(Main_Stack_Struct *stack_data, size_t new_capacity)
{
    RETURN_ERROR(stack_is_err(stack_data));

    if(new_capacity == stack_data->capacity)
        return ALL_IS_OK;

    StackElem_t *new_array = (StackElem_t*) realloc(stack_data->stack_array,
                                                    (new_capacity CANARIES(+ 2 * sizeof(canary_value))));

    if(new_array == nullptr)
    {
        fprintf(stderr, "stack RED_TEXT(couldn't realloced) at address:YELLOW_TEXT(%p\n)", new_array);
        return STACK_NOT_REALLOCED;
    }

    if(new_capacity > stack_data->capacity)
        memset((new_array + stack_data->size CANARIES(+ sizeof(canary_value))), Poison_Byte,
              (new_capacity - stack_data->size) * sizeof(StackElem_t));

    stack_data->capacity      = new_capacity;
    stack_data->stack_array   = new_array;

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                CANARIES(+ 2 * sizeof(canary_value))));

    CANARIES(ASSERT_FUNC(DEBUG_VAR(!)put_canaries(stack_data)));

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                CANARIES(+ 2 * sizeof(canary_value))));

    RETURN_ERROR(stack_is_err(stack_data));
    return ALL_IS_OK;

}


void put_stars(FILE* file)
{
    for(int i = 0; i < 50; i++)
    {
        fputc('*', file);
    }
    fputc('\n', file);
}


size_t realloc_if_up_needed(Main_Stack_Struct stack_data)
{
    if(stack_data.capacity - stack_data.size <= 1)
        return stack_data.capacity * 2;
    else
        return stack_data.capacity;
}


size_t realloc_if_down_needed(Main_Stack_Struct stack_data)
{
    if(4 <= stack_data.size && stack_data.size * 4 <= stack_data.capacity)
        return stack_data.capacity / 4;
    else
        return stack_data.capacity;
}

#ifdef DEBUG
void_sex return_error(size_t err_code, const char* file, const char* func, int line)
{
    if(err_code != 0)
    {
        fprintf(stderr, RED_TEXT("ERROR DETECTED IN ") MAGENTA_TEXT("%s:") BLUE_TEXT("%s:") GREEN_TEXT("%d\n")
                        RED_TEXT("ERROR SUM = ") GREEN_TEXT("%lu\n"), file, func, line, err_code);

        fprintf(stderr, MAGENTA_TEXT("\nERROR CODES:\n")
                        YELLOW_TEXT("STRUCT_ADDRESS_IS_BAD =  ")   RED_TEXT("2\n")
                        YELLOW_TEXT("NEG_CAPACITY          =  ")   RED_TEXT("4\n")
                        YELLOW_TEXT("WRONG_HASH            =  ")   RED_TEXT("8\n")
                        YELLOW_TEXT("STACK_OVERFLOW        = ")    RED_TEXT("16\n")
                        YELLOW_TEXT("FILE_PTR_IS_ZERO      = ")    RED_TEXT("32\n\n"));

        ASSERT(0);
    }
}
#endif


int is_struct_addresses_okay(Main_Stack_Struct *stack_data)
{
    if(stack_data && stack_data->stack_array)
        return 1;
    else
        return 0;
}


// Error_Codes fill_dead_bytes(char* array, size_t size)
// {
//     size_t num_of_dead_bytes = (size_t)array % size;

//     if(!num_of_dead_bytes)
//     {
//         return ALL_IS_OK;
//     }

//     memset(array, Dead_Byte, num_of_dead_bytes);
// }

#ifdef CANARY_MODE
Error_Codes put_canaries(Main_Stack_Struct *stack_data)
{
    RETURN_ERROR(stack_is_err(stack_data));

    *((uint64_t*)stack_data->stack_array) = canary_value;

    *((uint64_t*)(stack_data->stack_array + sizeof(canary_value) + stack_data->capacity)) = canary_value;

    HASH(stack_data->hash_struct = hash_struct_sum(stack_data);)

    HASH(stack_data->hash_stack = struct_elem_hash(stack_data->stack_array, stack_data->capacity
                                                   CANARIES(+ 2 * sizeof(canary_value))));

    RETURN_ERROR(stack_is_err(stack_data));
    return ALL_IS_OK;
}
#endif

#ifdef HASH_MODE
size_t struct_elem_hash(const void* address, size_t size)
{
    size_t hash = 5831;

    for(size_t i = 0; i < size; i++)
    {
        hash = hash * 33 ^ (size_t)((const uint8_t*)address + i);
    }

    return hash;
}
#endif


#ifdef HASH_MODE
size_t hash_struct_sum(Main_Stack_Struct *stack_data)
{
    size_t stack_hash = stack_data->hash_stack;
    stack_data->hash_stack = 0;

    size_t return_data = struct_elem_hash(stack_data, sizeof(*stack_data));
    stack_data->hash_stack = stack_hash;

    return return_data;
}
#endif
