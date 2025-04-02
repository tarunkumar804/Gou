#include <cstdint> // For uint32_t, uint64_t
#include <array>   // For std::array
#include <numeric> // Potentially for std::rotl, std::rotr in C++20 (or implement manually)
#include <concepts> // For C++20 concepts if using std::rotr/rotl
#include <limits>  // For numeric_limits

// C++20 bit operations (provide fallback if not available)
#if __cplusplus >= 202002L && defined(__has_include)
#if __has_include(<bit>)
#include <bit>
#define HAS_STD_ROTATIONS 1
#endif
#endif

class hashing {
public:
    // Public interface would go here (e.g., constructor, update, finalize methods)
    // For now, we keep the focus on improving the internal round function.

    // --- Constants (Example for SHA-256 K values - MUST be completed) ---
    // Should be constexpr static members if possible
    // static constexpr std::array<uint32_t, 64> K256 = { 0x428a2f98, 0x71374491, ... };
    // static constexpr std::array<uint64_t, 80> K512 = { 0x428a2f98d728ae22, 0x7137449123ef65cd, ... };

private: // Internal state and helpers should generally be private

    // --- State Structs using Standard Word Sizes ---
    struct sha256_state {
        // Use std::array for better C++ integration
        std::array<uint32_t, 8> H; // State variables (a-h)
    };

    struct sha512_state {
        std::array<uint64_t, 8> H; // State variables (a-h)
    };

    // --- Rotation Helper Functions ---
    // Use C++20 std::rotr if available, otherwise implement manually.
    // Marked inline for potential performance gain, constexpr if possible.

    template<typename T> requires (std::is_unsigned_v<T>)
    [[nodiscard]] static constexpr inline T rotate_right(T value, unsigned int count) noexcept {
        constexpr unsigned int bits = std::numeric_limits<T>::digits;
        count %= bits; // Ensure count is within valid range
        if (count == 0) return value;
#ifdef HAS_STD_ROTATIONS
        // Requires C++20 and <bit> header
         return std::rotr(value, count);
#else
        // Manual implementation
        return (value >> count) | (value << (bits - count));
#endif
    }

    // --- SHA-256 Compression Round (Operates IN-PLACE) ---
    // Modifies the state directly for efficiency (no copying state structs)
    // Takes Wt (derived word) and Kt (additive constant) with correct types
    static void SHA256_round(sha256_state& current_state, uint32_t Wt, uint32_t Kt) noexcept {
        // Load state into local variables (compilers often optimize this well)
        uint32_t a = current_state.H[0];
        uint32_t b = current_state.H[1];
        uint32_t c = current_state.H[2];
        uint32_t d = current_state.H[3];
        uint32_t e = current_state.H[4];
        uint32_t f = current_state.H[5];
        uint32_t g = current_state.H[6];
        uint32_t h = current_state.H[7];

        // Compute SHA-256 round functions using correct 32-bit operations
        uint32_t S1 = rotate_right(e, 6) ^ rotate_right(e, 11) ^ rotate_right(e, 25); // Σ1(e)
        uint32_t ch = (e & f) ^ (~e & g);                                          // Ch(e,f,g)
        uint32_t temp1 = h + S1 + ch + Kt + Wt;                                      // As per FIPS 180-4

        uint32_t S0 = rotate_right(a, 2) ^ rotate_right(a, 13) ^ rotate_right(a, 22); // Σ0(a)
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);                                  // Maj(a,b,c)
        uint32_t temp2 = S0 + maj;                                                   // As per FIPS 180-4

        // Update state variables (working backwards as per standard update description)
        current_state.H[7] = g;         // h' = g
        current_state.H[6] = f;         // g' = f
        current_state.H[5] = e;         // f' = e
        current_state.H[4] = d + temp1; // e' = d + temp1
        current_state.H[3] = c;         // d' = c
        current_state.H[2] = b;         // c' = b
        current_state.H[1] = a;         // b' = a
        current_state.H[0] = temp1 + temp2; // a' = temp1 + temp2
    }

    // --- SHA-512 Compression Round (Operates IN-PLACE) ---
    static void SHA512_round(sha512_state& current_state, uint64_t Wt, uint64_t Kt) noexcept {
        // Load state into local variables
        uint64_t a = current_state.H[0];
        uint64_t b = current_state.H[1];
        uint64_t c = current_state.H[2];
        uint64_t d = current_state.H[3];
        uint64_t e = current_state.H[4];
        uint64_t f = current_state.H[5];
        uint64_t g = current_state.H[6];
        uint64_t h = current_state.H[7];

        // Compute SHA-512 round functions using correct 64-bit operations
        uint64_t S1 = rotate_right(e, 14) ^ rotate_right(e, 18) ^ rotate_right(e, 41); // Σ1(e)
        uint64_t ch = (e & f) ^ (~e & g);                                           // Ch(e,f,g)
        uint64_t temp1 = h + S1 + ch + Kt + Wt;                                       // As per FIPS 180-4

        uint64_t S0 = rotate_right(a, 28) ^ rotate_right(a, 34) ^ rotate_right(a, 39); // Σ0(a)
        uint64_t maj = (a & b) ^ (a & c) ^ (b & c);                                   // Maj(a,b,c)
        uint64_t temp2 = S0 + maj;                                                    // As per FIPS 180-4

        // Update state variables
        current_state.H[7] = g;         // h' = g
        current_state.H[6] = f;         // g' = f
        current_state.H[5] = e;         // f' = e
        current_state.H[4] = d + temp1; // e' = d + temp1
        current_state.H[3] = c;         // d' = c
        current_state.H[2] = b;         // c' = b
        current_state.H[1] = a;         // b' = a
        current_state.H[0] = temp1 + temp2; // a' = temp1 + temp2
    }

    // Other private members would be needed for a full implementation:
    // - K constants arrays (K256, K512)
    // - Current hash state (sha256_state or sha512_state)
    // - Buffer for unprocessed message data
    // - Total message length counter
    // - Helper functions for padding, message scheduling (Wt generation), etc.
};
