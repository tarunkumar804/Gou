namespace blockchain{
    
    typedef struct block{
        char *ciphertext;
        char *public_key;
        char *private_key;
        char *hash;
        char *blockid;
        char *blockname;
    };
    
    typedef struct wallet {
        char *wallet_holder_name;
        uint2048_t wallet_key;
        uint8129_t wallet_address;
        char *public_key;
        char *private_key;
        char *hash;
    };
}
