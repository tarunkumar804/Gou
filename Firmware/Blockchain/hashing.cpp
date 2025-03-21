class hashing{
    public:
        uint2048_t rotations (uint2048_t number, long long int number_of_iterations){
            
            uint2048_t rotated_number = 0, temporary_number = 0;
            uint8_t carry_over = 0;
            
            for (long long int l = 0; l < number_of_iterations; l++)
            {
                temporary_number = number;
                number = number >> 1;
                carry_over = temporary_number - number;
                rotated_number = number | carry_over;
            }

            return rotated_number;
        }

        uint256_t* SHA256(uint256_t a, uint256_t b, uint256_t c, uint256_t d, uint256_t e, uint256_t f, uint256_t g, uint256_t h, uint64_t derived_word, uint64_t additive_constant, uint256_t input_block, long long int shift_iterations, long long int rotation_iterations){
            uint256_t *hash, temp_a, temp_d, temp_h;
            uint256_t sum_a = rotations(a, 28) ^ rotations(a, 34) ^ rotations(a, 39);
            uint256_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint256_t sum_e = rotations(e, 14) ^ (e, 18) ^ (e, 41);
            uint256_t ch = (e & f) ^ (~e & g);
            temp_a = sum_a ^ maj ^ additive_constant;
            temp_h = ch ^ h ^ sum_e ^ derived_word ^ additive_constant;
            temp_d = d ^ temp_h;
            hash = [temp_a, a, b, c, temp_d, f, f, g];
            return hash;
        }

        uint512_t* SHA512 (uint512_t a, uint512_t b, uint512_t c, uint512_t d, uint512_t e, uint512_t f, uint512_t g, uint512_t h, uint64_t derived_word, uint64_t additive_constant, uint512_t input_block, long long int shift_iterations, long long int rotation_iterations){
            uint512_t *hash, temp_a, temp_d, temp_h;
            uint512_t sum_a = rotations(a, 28) ^ rotations(a, 34) ^ rotations(a, 39);
            uint512_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint512_t sum_e = rotations(e, 14) ^ (e, 18) ^ (e, 41);
            uint512_t ch = (e & f) ^ (~e & g);
            temp_a = sum_a ^ maj ^ additive_constant;
            temp_h = ch ^ h ^ sum_e ^ derived_word ^ additive_constant;
            temp_d = d ^ temp_h;
            hash = [temp_a, a, b, c, temp_d, f, f, g];
            return hash;
        }
        
        char* bcrypt() {
            char *hash;
            return hash;
        }
};