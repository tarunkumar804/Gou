class hashing {
    public:
        uint32_t* SHA256 (uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h, uint32_t derived_word, uint32_t additive_constant) //Please consult the SHA256 specification for the implementation.
        {
            x86_instructions i386 = new x86_instructions();
            uint32_t copies  = {a,b,c,d,e,f,g,h};

            uint32_t maj = (a&b) ^ (a&c) ^ (b&c);
            uint32_t ch = (e&f) ^ (~e&~g);
            uint32_t sum_a = i386.rotations(a,28) ^ i386.rotations (a,34) ^ i386.rotations (a,39);
            uint32_t sum_e = i386.rotations(e,14) ^ i386.rotations(e,18) ^ i386.rotations(e,15);
            copies[7] = copies[7] ^ ch ^ sum_e ^ derived_word ^ additive_constant;
            copies[0] = a ^ sum_a ^ maj ^ a ^ h;
            copies[1] = a;
            copies[2] = b;
            copies[3] = c;
            copies[4] = copies[7] ^ h;
            copies[5] = e;
            copies[6] = f;
            copies[7] = g;

            return copies;
        }

        uint64_t SHA512 (uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h, uint64_t derived_word, uint64_t additive_constant)
        {
            x86_instructions i386 = new x86_instructions();
            uint64_t copies  = {a,b,c,d,e,f,g,h};

            uint64_t maj = (a&b) ^ (a&c) ^ (b&c);
            uint64_t ch = (e&f) ^ (~e&~g);
            uint64_t sum_a = i386.rotations(a,28) ^ i386.rotations (a,34) ^ i386.rotations (a,39);
            uint64_t sum_e = i386.rotations(e,14) ^ i386.rotations(e,18) ^ i386.rotations(e,15);
            copies[7] = copies[7] ^ ch ^ sum_e ^ derived_word ^ additive_constant;
            copies[0] = a ^ sum_a ^ maj ^ a ^ h;
            copies[1] = a;
            copies[2] = b;
            copies[3] = c;
            copies[4] = copies[7] ^ h;
            copies[5] = e;
            copies[6] = f;
            copies[7] = g;

            return copies;
        }
};
