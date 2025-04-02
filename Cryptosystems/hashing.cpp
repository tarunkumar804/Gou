class hashing {
    public:
        uint32_t* SHA256 (uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h, uint32_t derived_word, uint32_t additive_constant) //Please consult the SHA256 specification for the implementation.
        {
            /** A function to implement SHA256.
            * @authors Tarun Kumar.
            * @param a - A 32-bit block of the original message.
            * @param b - A 32-bit block of the original message.
            * @param c - A 32-bit block of the original message.
            * @param d - A 32-bit block of the original message.
            * @param e - A 32-bit block of the original message.
            * @param f - A 32-bit block of the original message.
            * @param g - A 32-bit block of the original message.
            * @param h - A 32-bit block of the original message.
            * @param derived_word - A word derived from the 256-bit block.
            * @param additive_constant - A 32-bit additive constant.
            * @return An array containing the 256-bit hash in 32-bit blocks.
            */

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

            return copies; // So that the original contents are not overwritten.
        }

        uint64_t SHA512 (uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h, uint64_t derived_word, uint64_t additive_constant)
        {
            /** A function to implement SHA256.
            * @authors Tarun Kumar.
            * @param a - A 64-bit block of the original message.
            * @param b - A 64-bit block of the original message.
            * @param c - A 64-bit block of the original message.
            * @param d - A 64-bit block of the original message.
            * @param e - A 64-bit block of the original message.
            * @param f - A 64-bit block of the original message.
            * @param g - A 64-bit block of the original message.
            * @param h - A 64-bit block of the original message.
            * @param derived_word - A word derived from the 512-bit block.
            * @param additive_constant - A 64-bit additive constant.
            * @return An array containing the 512-bit hash in 64-bit blocks.
            */


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

            return copies; //So that the original contents are not overwritten.
        }
};
