/* I might use duck typing */
typedef enum type_name {
    /*should be auto generated but contain atleast*/
    Integer, Real, Char, Array, Tuple, Function, Object
} type_name;

typedef struct type {
    type_name name;
    type** supertypes;
    int num_supertypes;

    int num_type_arguements;
    type** type_arguements;
} type;
/**/

typedef struct object {
    // type type;
    
} object;

void object_set (object* self, char* key, object* value);
void object_remove (object* self, char* key);
object* object_get (object* self, char* value);
