#include <iostream>
#include <vector>
#include <limits>       // For std::numeric_limits
#include <stdexcept>    // For exceptions
#include <random>       // For std::random_device, std::mt19937_64, distributions
#include <chrono>       // For time-based seeding
#include <concepts>     // For C++20 concepts (optional but good)
#include <functional>   // For std::function
#include <string>       // For state representation
#include <sstream>      // For string manipulation
#include <iomanip>      // For hex output

// --- Dependency Handling for uint8192_t ---
// Option 1: Assume a header defines it (like boost::multiprecision or a custom one)
// #include "large_int.hpp" // Example placeholder
// using uint8192_t = CppIntNamespace::uint8192_t; // Adjust namespace

// Option 2: For demonstration, let's alias it to uint64_t if not defined elsewhere.
//            Note: Operations might behave differently with true large integers.
#ifndef UINT8192_T_DEFINED // Simple guard, replace with actual check if needed
using uint8192_t = uint64_t;
#define UINT8192_T_DEFINED
// Add necessary operators if uint8192_t is a custom class without them defined globally
#endif
// --- End Dependency Handling ---


// --- C++20 Concept for Unsigned Integral types (Optional) ---
#if __cplusplus >= 202002L
template <typename T>
concept UnsignedIntegral = std::is_integral_v<T> && std::is_unsigned_v<T>;
#else
// Fallback for pre-C++20: Use template specialization or SFINAE if needed,
// otherwise just rely on compiler errors for invalid types.
#define UnsignedIntegral typename
#endif
// --- End Concept ---


template <UnsignedIntegral T = uint64_t> // Default to uint64_t, allows customization
class rngs {
private:
    T state;                    // Primary state for custom generators
    std::mt19937_64 mt_engine;  // Standard Mersenne Twister engine for reliable randomness

    // --- Internal Helper Functions ---

    // Seed using std::random_device and time for better entropy
    void seed_internal() {
        std::random_device rd;
        // Use multiple random_device results and time for a better seed sequence
        std::seed_seq sseq{
            rd(), rd(), rd(), rd(),
            static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())
        };
        mt_engine.seed(sseq);

        // Initialize custom state 'state' using the seeded MT engine
        // This needs care if T is larger than uint64_t
        if constexpr (sizeof(T) <= sizeof(uint64_t)) {
            state = static_cast<T>(mt_engine());
        } else {
            // For larger types (like uint8192_t), fill it piece by piece
            // This assumes T can be manipulated with bitwise ops and sizeof works.
            constexpr size_t num_chunks = (sizeof(T) + sizeof(uint64_t) - 1) / sizeof(uint64_t);
            state = 0; // Start with zero
            for (size_t i = 0; i < num_chunks; ++i) {
                // Check T supports operator<< and operator| before enabling this
                 // T chunk = static_cast<T>(mt_engine());
                 // state |= (chunk << (i * 64));
                 // Fallback: Just use the first chunk for simplicity if operators missing
                 if (i == 0) state = static_cast<T>(mt_engine());
            }
             // If state remains 0 (e.g., only one chunk failed), set a default non-zero
             if (state == 0) state = static_cast<T>(1);
        }
         // Ensure state is non-zero for algorithms that require it (like xorshift)
         if (state == 0) {
            state = static_cast<T>(1); // Or another default non-zero value
         }
    }

    // Rotate Left (ROL) - essential for many PRNGs and oscillator models
    T rotate_left(T value, unsigned int count) const {
        constexpr unsigned int num_bits = std::numeric_limits<T>::digits;
        if (count == 0 || num_bits == 0) return value; // Handle no-op and non-numeric T
        count %= num_bits; // Ensure count is within bounds
        if (count == 0) return value;
        return (value << count) | (value >> (num_bits - count));
    }

    // Rotate Right (ROR)
    T rotate_right(T value, unsigned int count) const {
        constexpr unsigned int num_bits = std::numeric_limits<T>::digits;
        if (count == 0 || num_bits == 0) return value;
        count %= num_bits;
        if (count == 0) return value;
        return (value >> count) | (value << (num_bits - count));
    }


public:
    // --- Constructors ---

    // Default constructor: Seeds using internal helper
    rngs() {
        seed_internal();
    }

    // Constructor with explicit seed value
    explicit rngs(T initial_seed) : state(initial_seed), mt_engine(initial_seed) {
        // Ensure initial state is valid if necessary (e.g., non-zero)
        if (state == 0) {
            state = static_cast<T>(1); // Or seed_internal();
        }
    }

    // Constructor using a seed sequence (more robust seeding)
    template<typename SeedSeq>
    explicit rngs(SeedSeq& q) : mt_engine(q) {
         // Initialize custom state 'state' using the seeded MT engine
        if constexpr (sizeof(T) <= sizeof(uint64_t)) {
            state = static_cast<T>(mt_engine());
        } else {
            // Fill larger T piece by piece (improve this based on T's capabilities)
            state = static_cast<T>(mt_engine()); // Simplified fill
        }
        if (state == 0) state = static_cast<T>(1);
    }


    // --- Seeding ---

    // Reseed with a specific value
    void seed(T new_seed) {
        state = new_seed;
        mt_engine.seed(new_seed);
        if (state == 0) state = static_cast<T>(1);
    }

    // Reseed using random_device and time
    void auto_seed() {
        seed_internal();
    }

    // Reseed using a seed sequence
    template<typename SeedSeq>
    void seed(SeedSeq& q) {
        mt_engine.seed(q);
        // Re-initialize custom state 'state'
        if constexpr (sizeof(T) <= sizeof(uint64_t)) {
            state = static_cast<T>(mt_engine());
        } else {
             state = static_cast<T>(mt_engine()); // Simplified fill
        }
       if (state == 0) state = static_cast<T>(1);
    }


    // --- Core Generator Interface (like <random>) ---

    using result_type = T;
    static constexpr T min() { return std::numeric_limits<T>::min(); }
    static constexpr T max() { return std::numeric_limits<T>::max(); }

    // Default generator: Uses a basic Xorshift variant (adjust params based on T)
    T operator()() {
        // Example: xorshift* parameters for 64-bit. Needs adaptation for T.
        if constexpr (std::is_same_v<T, uint64_t>) {
            state ^= state >> 12; // a
            state ^= state << 25; // b
            state ^= state >> 27; // c
            return state * 0x2545F4914F6CDD1DULL; // xorshift* result
        }
        // Example: Basic xorshift for 32-bit
        else if constexpr (std::is_same_v<T, uint32_t>) {
             state ^= state << 13;
             state ^= state >> 17;
             state ^= state << 5;
             return state;
        }
        // Fallback for other/large types: Use a simple modification or MT engine
        else {
            // Simple state modification (e.g., rotate and XOR)
            state = rotate_left(state, (sizeof(T) > 4 ? 15 : 7)); // Rotate amount depends on size
            state ^= (state >> (sizeof(T) > 4 ? 21 : 11));
             // Ensure result isn't 0 if possible (depends on T's capabilities)
             if (state == 0) state = static_cast<T>(mt_engine());
             if (state == 0) state = static_cast<T>(1);
            return state;

            // Alternative Fallback: Use the internal Mersenne Twister (may truncate if T > uint64_t)
            // return static_cast<T>(mt_engine());
        }
    }


    // --- Original ring_oscillator (Improved Logic) ---

    // Simulates steps of combined operations, closer to a feedback loop model
    // Returns the final state after 'num_steps'.
    T ring_oscillator_step(T initial_value,
                           unsigned int num_steps,
                           unsigned int shift_amount,
                           T xor_mask, // Mask to XOR with
                           T not_mask = max(), // Mask for NOT (~) op (max() = all bits)
                           char shift_direction = 'L', // 'L' or 'R'
                           bool rotate = true) // Use rotation instead of plain shift
    {
        if (shift_direction != 'L' && shift_direction != 'R') {
            throw std::invalid_argument("Shift direction must be 'L' or 'R'");
        }

        T current_val = initial_value;

        for (unsigned int i = 0; i < num_steps; ++i) {
            // 1. Apply NOT (bitwise complement) based on mask
            current_val ^= not_mask; // XOR with all 1s is equivalent to NOT

            // 2. Apply Shift or Rotation
            if (shift_amount > 0) {
                if (rotate) {
                     current_val = (shift_direction == 'L')
                                    ? rotate_left(current_val, shift_amount)
                                    : rotate_right(current_val, shift_amount);
                } else {
                     current_val = (shift_direction == 'L')
                                    ? (current_val << shift_amount)
                                    : (current_val >> shift_amount);
                }
            }

            // 3. Apply XOR with mask
            current_val ^= xor_mask;

            // Optional: Add feedback from previous state or other non-linear steps here
        }
        return current_val;
    }

    // Convenience method to run the oscillator simulation on the internal state
    T run_oscillator_on_state(unsigned int num_steps, unsigned int shift_amount, T xor_mask, T not_mask = max(), char shift_direction = 'L', bool rotate = true) {
        state = ring_oscillator_step(state, num_steps, shift_amount, xor_mask, not_mask, shift_direction, rotate);
        if (state == 0) state = static_cast<T>(1); // Ensure state doesn't become invalid 0
        return state;
    }


    // --- Additional RNG Algorithms ---

    // Linear Congruential Generator (LCG) - Use with caution, parameters are crucial!
    // Uses internal state. Parameters 'a', 'c', 'm' provided by user.
    // Note: Modulo 'm' might be tricky for very large T without library support.
    T lcg(T a, T c, T m) {
        // Basic protection against bad parameters
        if (m == 0) {
            // Use max value as modulus if m=0, or throw error
            m = max();
             // Or: throw std::invalid_argument("LCG modulus 'm' cannot be zero");
        }
        // Calculation: state = (a * state + c) % m;
        // This requires T to support multiplication, addition, and modulo.
        // For standard types, overflow needs consideration before modulo.
        // For large int libraries, this *should* work correctly.
        // Example assuming T has operators (may need adjustment for specific libraries):
         try {
             // Perform operations carefully for standard types to avoid premature overflow
             if constexpr (sizeof(T) <= sizeof(unsigned long long)) {
                 // Assuming T fits within standard types where manual overflow handling might be needed
                 // or rely on implicit unsigned wrap-around. This is simplified.
                 unsigned long long temp_a = static_cast<unsigned long long>(a);
                 unsigned long long temp_c = static_cast<unsigned long long>(c);
                 unsigned long long temp_m = static_cast<unsigned long long>(m);
                 unsigned long long current_state = static_cast<unsigned long long>(state);

                 // Calculate (a * state) % m carefully if intermediate product exceeds ULLONG_MAX
                 // Simplified: assumes wrap-around or T handles large numbers
                 current_state = (temp_a * current_state + temp_c) % temp_m;
                 state = static_cast<T>(current_state);

             } else {
                 // Assume T is a large integer type that handles arithmetic correctly
                 state = (a * state + c);
                 if (m != max()) { // Avoid modulo if m is the max value (implicit wrap)
                    state = state % m;
                 }
             }
         } catch (const std::exception& e) {
              // Handle potential exceptions from large number library arithmetic
              std::cerr << "LCG arithmetic error: " << e.what() << std::endl;
              // Recover or re-seed? Let's just use MT engine value as fallback
              state = static_cast<T>(mt_engine());
              if (state == 0) state = 1;
         }

        if (state == 0 && m != 1) state = static_cast<T>(1); // Avoid zero state if possible
        return state;
    }

    // Generate using the internal std::mt19937_64 engine
    uint64_t generate_mt() {
        return mt_engine();
    }


    // --- Output Formatting and Distributions ---

    // Generate a random number in a specified range [min_val, max_val] (inclusive)
    // Uses the default operator() generator. NOTE: Simple modulo method is biased!
    T range_biased(T min_val, T max_val) {
         if (min_val > max_val) {
            throw std::invalid_argument("min_val cannot be greater than max_val");
         }
         T range_size = (max_val - min_val); // Potential overflow if max_val=max() and min_val=0

         // Handle full range
         if (min_val == min() && max_val == max()) {
             return (*this)(); // Call operator()
         }

        // Avoid division by zero if range_size wraps around to 0 (max_val - min_val + 1 calculation)
        if (range_size == max()) { // This check covers the case max_val=max, min_val=0
            return (*this)();
        }

        // Calculate actual size of range + 1
        T count = range_size + 1;
        if (count == 0) { // If +1 caused wrap-around (range covers entire type space)
             return (*this)();
        }

        // Basic modulo mapping (biased if count doesn't divide max()+1)
        return min_val + ((*this)() % count);
    }

    // Generate in range using the internal MT engine (less bias via std::uniform_int_distribution)
    // Note: std::uniform_int_distribution might not support custom large T types directly.
    // This example works best when RangeType is a standard integer type.
    template <typename RangeType = T>
    RangeType range_uniform(RangeType min_val, RangeType max_val) {
        // Requires RangeType to be usable with std::uniform_int_distribution
        // Typically standard integer types (int, long long, unsigned, etc.)
        try {
            std::uniform_int_distribution<RangeType> dist(min_val, max_val);
            return dist(mt_engine);
        } catch (const std::exception& e) {
            std::cerr << "Error using uniform_int_distribution: " << e.what() << std::endl;
            // Fallback to biased method or rethrow
             using FallbackType = typename std::conditional<std::is_signed_v<RangeType>, long long, unsigned long long>::type;
             FallbackType fb_min = static_cast<FallbackType>(min_val);
             FallbackType fb_max = static_cast<FallbackType>(max_val);
             FallbackType range_size = fb_max - fb_min + 1;
             if (range_size == 0) return static_cast<RangeType>(mt_engine()); // Full range fallback
             return static_cast<RangeType>(fb_min + (mt_engine() % range_size));
        }
    }

    // Generate a floating point number in [0.0, 1.0) using the internal MT engine
    double uniform_double_01() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(mt_engine);
    }

    // Generate a floating point number in [min_val, max_val) using the internal MT engine
    double uniform_double_range(double min_val, double max_val) {
        std::uniform_real_distribution<double> dist(min_val, max_val);
        return dist(mt_engine);
    }

    // Generate a normally distributed number using the internal MT engine
    double normal_double(double mean = 0.0, double stddev = 1.0) {
        std::normal_distribution<double> dist(mean, stddev);
        return dist(mt_engine);
    }

    // Generate a boolean value with a given probability p_true of being true
    bool bernoulli(double p_true = 0.5) {
        std::bernoulli_distribution dist(p_true);
        return dist(mt_engine);
    }


    // --- State Management ---

    // Get the current internal state of the custom generator
    T get_state() const {
        return state;
    }

    // Set the internal state of the custom generator
    void set_state(T new_state) {
        state = new_state;
         if (state == 0) state = static_cast<T>(1); // Ensure non-zero state
    }

    // Get the state of the internal Mersenne Twister engine (e.g., for saving/loading)
    std::mt19937_64& get_mt_engine() {
        return mt_engine;
    }

    // Set the state of the internal Mersenne Twister engine
    void set_mt_engine(const std::mt19937_64& engine_state) {
        mt_engine = engine_state;
    }

    // Get state as a hex string (useful for large numbers)
    std::string get_state_hex() const {
        // This requires T to be streamable or convertible.
        // May need specific implementation for custom large int types.
        std::stringstream ss;
        // Assuming T supports direct streaming to hex
        ss << std::hex << std::showbase << state;
        return ss.str();

        // TODO: Add specific handling for uint8192_t if needed, e.g., iterating chunks
    }

    // Set state from a hex string
    bool set_state_hex(const std::string& hex_str) {
        std::stringstream ss(hex_str);
        ss << std::hex;
        // Assuming T supports streaming extraction from hex
        T new_state;
        ss >> new_state;
        if (!ss.fail() && ss.eof()) { // Check if parsing was successful
            state = new_state;
            if (state == 0) state = static_cast<T>(1);
            return true;
        }
        return false;
        // TODO: Add specific handling for uint8192_t if needed
    }


    // --- Utility Functions ---

    // Get a specific bit (0 = least significant)
    bool get_bit(unsigned int bit_index) const {
        constexpr unsigned int num_bits = std::numeric_limits<T>::digits;
        if (bit_index >= num_bits) {
            throw std::out_of_range("Bit index out of range");
        }
        return (state >> bit_index) & static_cast<T>(1);
    }

    // Set a specific bit (0 = least significant)
    void set_bit(unsigned int bit_index, bool value) {
         constexpr unsigned int num_bits = std::numeric_limits<T>::digits;
        if (bit_index >= num_bits) {
            throw std::out_of_range("Bit index out of range");
        }
        T mask = static_cast<T>(1) << bit_index;
        if (value) {
            state |= mask;
        } else {
            state &= ~mask;
        }
         if (state == 0) state = static_cast<T>(1); // Ensure non-zero state after modification
    }

     // Count number of set bits (population count)
     // Requires support from T or standard library functions
     int popcount() const {
         if constexpr (sizeof(T) <= sizeof(unsigned long long)) {
             // Use C++20 <bit> header if available
             #if __cplusplus >= 202002L && defined(__cpp_lib_bitops)
             return std::popcount(static_cast<unsigned long long>(state));
             #else
             // Fallback using GCC/Clang builtins or manual count for standard types
             if constexpr (sizeof(T) == sizeof(unsigned int))
                 return __builtin_popcount(static_cast<unsigned int>(state));
             if constexpr (sizeof(T) == sizeof(unsigned long))
                 return __builtin_popcountl(static_cast<unsigned long>(state));
             if constexpr (sizeof(T) == sizeof(unsigned long long))
                 return __builtin_popcountll(static_cast<unsigned long long>(state));
             // Manual fallback (slow)
             int count = 0;
             T temp = state;
             while (temp > 0) {
                 temp &= (temp - 1); // Clears the least significant set bit
                 count++;
             }
             return count;
             #endif
         } else {
             // Popcount for large integer types needs library support
             // Placeholder: return -1 indicating not implemented or unknown
             // Or implement manually if T allows bit access
              // Manual fallback (slow)
             int count = 0;
             T temp = state;
             while (temp > 0) {
                 temp &= (temp - 1); // Assumes T supports these ops
                 count++;
             }
             return count;
             // return -1; // Indicate not implemented
         }
     }
};

// --- Example Usage ---
int main() {
    // Example using default uint64_t
    rngs<> gen64; // Automatically seeded
    std::cout << "Using uint64_t:" << std::endl;
    std::cout << "State (Hex): " << gen64.get_state_hex() << std::endl;
    std::cout << "Generated value: " << gen64() << std::endl;
    std::cout << "Uniform double [0,1): " << gen64.uniform_double_01() << std::endl;
    std::cout << "Range [10, 20]: " << gen64.range_uniform<int>(10, 20) << std::endl; // Use uniform range
    std::cout << "Popcount of state: " << gen64.popcount() << std::endl;
    std::cout << "Bit 5: " << gen64.get_bit(5) << std::endl;
    gen64.set_bit(5, !gen64.get_bit(5)); // Flip bit 5
    std::cout << "State after flipping bit 5: " << gen64.get_state_hex() << std::endl;
    std::cout << "Run oscillator on state: " << gen64.run_oscillator_on_state(10, 3, 0xAAAAAAAAAAAAAAAA, 0, 'L', true) << std::endl;


    std::cout << "\n---\n" << std::endl;

    // Example using the potentially large uint8192_t (aliased to uint64_t here)
    // If uint8192_t is a real large int type, ensure it has necessary operators.
    rngs<uint8192_t> gen_large(12345); // Seed with 12345
    std::cout << "Using uint8192_t (currently aliased to " << typeid(uint8192_t).name() << "):" << std::endl;
    std::cout << "Initial State (Hex): " << gen_large.get_state_hex() << std::endl;
    std::cout << "Generated value 1: " << gen_large.get_state_hex() << std::endl; // operator() modifies state
    gen_large(); // Generate next state
    std::cout << "Generated value 2: " << gen_large.get_state_hex() << std::endl;
    // Note: range_uniform might fallback or fail if uint8192_t isn't a standard type
    // std::cout << "Range [0, 100]: " << gen_large.range_uniform<uint8192_t>(0, 100) << std::endl;
    std::cout << "Range [0, 100] (biased): " << gen_large.range_biased(0, 100) << std::endl; // Use biased range for custom types

    // Use the oscillator function directly
    uint8192_t osc_result = gen_large.ring_oscillator_step(gen_large.get_state(), 5, 65, 123, 0xFF, 'R', true);
    std::cout << "Oscillator result (direct call): ";
    // Need a way to print uint8192_t if it's custom
     std::cout << std::hex << osc_result << std::dec << std::endl;


    return 0;
}
