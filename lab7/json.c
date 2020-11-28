#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum category {CA_OBJECT, CA_ARRAY, CA_STRING, CA_NUMBER, CA_BOOLEAN, CA_VNULL} Category;

typedef union u_val{
    struct Object *object;
    struct Array *array;
    char *string;
    double number;
    int b;
} Union_val;

typedef struct Json {
    // enum  {OBJECT, ARRAY, STRING, INTEGER, DOUBLE, BOOLEAN, VNULL} category;
    Category category;
    Union_val val;
} Json;

typedef struct Object {
    char *key;
    struct Json *value;
    struct Object *next_object;
} Object;

typedef struct Array
{
    struct Json *value;
    struct Array *next_value;
} Array;

Json *init_json(Category category) {
    Json *ptr = (Json *)malloc(sizeof(Json));
    ptr->category = category;
    return ptr;
}

Object* init_object(){
    Object* object = (Object*) malloc(sizeof(Object));
    return object;
}

Array* init_array(){
    Array* array = (Array*) malloc(sizeof(Array));
    return array;
}

// void init_string(Json *ptr, char* str) {
//     int len = strlen(str);
//     char *new_ptr = (char *)malloc(len * sizeof(char));
//     strcpy(new_ptr, str);
//     Union_val val;
//     val.string = str;
//     init_val(STRING);
// }

// void init_double(Json *ptr, double d) {
//     Union_val val;
//     val.double_number = d;
//     init_val(DOUBLE);
// }

// void init_integer(Json *ptr, int i) {
//     Union_val val;
//     val.integer_number = i;
//     init_val(ptr, INTEGER, val);
// }