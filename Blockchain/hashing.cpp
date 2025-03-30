class hashing {
public:
    // Structs to hold SHA-256 and SHA-512 state (8 words each)
    struct sha256_state {
        uint256_t values[8];
    };

    struct sha512_state {
        uint512_t values[8];
    };

    // SHA-256 compression round
    sha256_state SHA256_round(const uint256_t& a, const uint256_t& b, const uint256_t& c, const uint256_t& d,
                              const uint256_t& e, const uint256_t& f, const uint256_t& g, const uint256_t& h,
                              uint64_t derived_word, uint64_t additive_constant) {
        sha256_state state;

        // Compute SHA-256 round functions
        uint256_t sum_a = rotations(a, 2) ^ rotations(a, 13) ^ rotations(a, 22);  // Σ0
        uint256_t maj = (a & b) ^ (a & c) ^ (b & c);                             // Majority
        uint256_t sum_e = rotations(e, 6) ^ rotations(e, 11) ^ rotations(e, 25); // Σ1
        uint256_t ch = (e & f) ^ (~e & g);                                       // Choice

        // Temporary values (using addition as per SHA-256 standard)
        uint256_t temp1 = h + sum_e + ch + uint256_t(derived_word) + uint256_t(additive_constant);
        uint256_t temp2 = sum_a + maj;

        // Update state
        state.values[0] = temp1 + temp2;  // a' = temp1 + temp2
        state.values[1] = a;              // b' = a
        state.values[2] = b;              // c' = b
        state.values[3] = c;              // d' = c
        state.values[4] = d + temp1;      // e' = d + temp1
        state.values[5] = e;              // f' = e
        state.values[6] = f;              // g' = f
        state.values[7] = g;              // h' = g

        return state;
    }

    // SHA-512 compression round
    sha512_state SHA512_round(const uint512_t& a, const uint512_t& b, const uint512_t& c, const uint512_t& d,
                              const uint512_t& e, const uint512_t& f, const uint512_t& g, const uint512_t& h,
                              uint64_t derived_word, uint64_t additive_constant) {
        sha512_state state;

        // Compute SHA-512 round functions
        uint512_t sum_a = rotations(a, 28) ^ rotations(a, 34) ^ rotations(a, 39); // Σ0
        uint512_t maj = (a & b) ^ (a & c) ^ (b & c);                             // Majority
        uint512_t sum_e = rotations(e, 14) ^ rotations(e, 18) ^ rotations(e, 41); // Σ1
        uint512_t ch = (e & f) ^ (~e & g);                                       // Choice

        // Temporary values (using addition as per SHA-512 standard)
        uint512_t temp1 = h + sum_e + ch + uint512_t(derived_word) + uint512_t(additive_constant);
        uint512_t temp2 = sum_a + maj;

        // Update state
        state.values[0] = temp1 + temp2;  // a' = temp1 + temp2
        state.values[1] = a;              // b' = a
        state.values[2] = b;              // c' = b
        state.values[3] = c;              // d' = c
        state.values[4] = d + temp1;      // e' = d + temp1
        state.values[5] = e;              // f' = e
        state.values[6] = f;              // g' = f
        state.values[7] = g;              // h' = g

        return state;
    }

private:
    // Placeholder for rotations function (should be implemented based on uint256_t/uint512_t type)
    uint256_t rotations(const uint256_t& x, int n);
    uint512_t rotations(const uint512_t& x, int n);
};
