typedef struct Json {
    enum {OBJECT, ARRAY, STRING, NUMBER, BOOLEAN, VNULL} category;
    union{
        struct Object *object;
        struct Array *array;
        char *string;
        double number;
        enum {TRUE, FALSE} boolean;
    };
} Json;

typedef struct Object {
    char *string;
    struct Json *value;
    struct Object *next_object;
} Object;

typedef struct Array
{
    struct Json *value;
    struct Array *next_value;
} Array;
