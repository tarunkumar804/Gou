namespace data_structure_primitives{

    typedef struct node{
        char *contents; //Data as a string.
        node *next;
        node *prev;
        node *loopback; // A pointer to the starting node like a loopback address.
    };

    typedef struct data_container{
        uint8192_t length_of_data_container;
        char *data_container [length_of_data_container];
    };

    typedef struct stack{
        int8192_t top;
        int8192_t length_of_array;
        int8192_t array [length_of_array];
    };

    typedef struct queue{
        int8192_t front;
        int8192_t back;
        int8192_t length_of_array;
        int8192_t array [length_of_array];
    };
}
