namespace io{

    typedef struct file_block{ // Data block of a file.
        uint8192_t length_of_block;
        char *block [length_of_block];
    };

    typedef struct 
}