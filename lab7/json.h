// #ifndef JSON_H
// #define JSON_H

// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

// enum boolean {CA_FALSE, CA_TRUE};
// typedef enum category {CA_OBJECT, CA_ARRAY, CA_STRING, CA_INTEGER, CA_DOUBLE, CA_BOOLEAN, CA_VNULL} Category;

// typedef union u_val{
//     struct Object *object;
//     struct Array *array;
//     char *string;
//     double double_number;
//     int integer_number;
//     enum boolean b;
// } Union_val;

// typedef struct Json {
//     // enum  {OBJECT, ARRAY, STRING, INTEGER, DOUBLE, BOOLEAN, VNULL} category;
//     Category category;
//     Union_val val;
// } Json;

// typedef struct Object {
//     char *key;
//     struct Json *value;
//     struct Object *next_object;
// } Object;

// typedef struct Array
// {
//     struct Json *value;
//     struct Array *next_value;
// } Array;

// #endif