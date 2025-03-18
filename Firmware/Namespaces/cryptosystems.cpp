namespace cryptosystem{
    typedef struct keystreams{
        char *private_key;
        char *public_key;
    };

    typedef struct playfair{
        char *message;
        char key_block[26][26];
        char *ciphertext;
    };

    typedef struct AES{
        char *keystream;
        uint8192_t rows;
        uint8192_t columns;
        uint8192 block[rows][columns];
        uint8192_t s_box [rows][columns];
        uint8192_t inverse_s_box [rows][columns];
        uint8192_t key_expansion_block [rows][columns];
    };
    
    typedef struct RSA{
        uint8192_t p;
        uint8192_t q;
        uint8192_t phi = (p-1) * (q-1);
        uint8192_t d;
        char *message;
        char *ciphertext;
    };
}