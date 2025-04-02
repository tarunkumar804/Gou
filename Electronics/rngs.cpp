#include <cstdint> // For uint64_t
#include <stdexcept> // For std::invalid_argument
#include <limits> // For numeric_limits

class rngs {
public:
    // Enum for clarity and type safety on shift direction
    enum class ShiftDirection {
        LEFT,
        RIGHT
    };

    /**
     * @brief Simulates a sequence of bitwise operations (NOT, Shift, XOR).
     *
     * NOTE: This function attempts to interpret the flawed logic of the original.
     * The sequence of operations (all NOTs, then all Shifts, then all XORs)
     * and the XOR operation (^ 1) are unlikely to produce high-quality random numbers
     * or accurately simulate a hardware ring oscillator or LFSR for RNG purposes.
     * The original uint8192_t type has been replaced with uint64_t for efficiency.
     *
     * @param num_not_ops Number of bitwise NOT operations to apply.
     * @param num_shift_ops Number of shift operations to apply.
     * @param num_xor_ops Number of XOR-with-1 operations to apply.
     * @param direction The direction for shift operations (LEFT or RIGHT).
     * @param initial_seed The starting value for the operations.
     * @return The result after applying all operations.
     * @throws std::invalid_argument if direction is invalid (shouldn't happen with enum).
     */
    // Make static if it doesn't depend on class instance members
    // Mark noexcept as core operations don't throw
    static uint64_t simulate_bitwise_sequence(
        uint64_t num_not_ops,         // Use native types, pass by value is efficient
        uint64_t num_shift_ops,
        uint64_t num_xor_ops,
        ShiftDirection direction,     // Use enum
        uint64_t initial_seed         // Use appropriate unsigned type for seed
    ) noexcept {                     // Mark noexcept

        uint64_t current_value = initial_seed;

        // 1. Apply NOT operations
        // Check if the number of NOT ops is odd, as ~ (~x) == x
        if (num_not_ops % 2 != 0) {
            current_value = ~current_value;
        }
        // If num_not_ops is very large, the % 2 is much faster than a loop.
        // If a loop was truly intended (e.g., timing simulation), use:
        // for (uint64_t i = 0; i < num_not_ops; ++i) {
        //     current_value = ~current_value;
        // }


        // 2. Apply Shift operations
        // Prevent excessive shifts beyond the type's width
        constexpr unsigned int bits = std::numeric_limits<uint64_t>::digits;
        // Note: Shifting by >= number of bits is undefined behavior in C++.
        // Cap the shift amount, although the loop handles this implicitly.
        // If num_shift_ops could be >= bits, clamping might be needed before the loop:
        // num_shift_ops = std::min(num_shift_ops, static_cast<uint64_t>(bits -1));

        if (direction == ShiftDirection::LEFT) {
            for (uint64_t i = 0; i < num_shift_ops && i < bits; ++i) { // Avoid UB loop condition
                 // Check if we'd shift out all bits - result would be 0
                if (current_value == 0) break;
                current_value <<= 1;
            }
        } else { // RIGHT
            for (uint64_t i = 0; i < num_shift_ops && i < bits; ++i) { // Avoid UB loop condition
                 // Check if we'd shift out all bits - result would be 0
                if (current_value == 0) break;
                current_value >>= 1;
            }
        }


        // 3. Apply XOR operations
        // Similar optimization: XORing with 1 N times is equivalent to
        // XORing once if N is odd, and doing nothing if N is even.
        if (num_xor_ops % 2 != 0) {
            current_value ^= 1; // XOR with 1 flips the LSB
        }
        // If a loop was intended:
        // for (uint64_t i = 0; i < num_xor_ops; ++i) {
        //     current_value ^= 1;
        // }


        return current_value;
    }


    // --- Original function name kept for reference, now calls the improved one ---
    // --- Consider removing this wrapper eventually ---
    [[deprecated("Use simulate_bitwise_sequence with ShiftDirection enum and uint64_t types. Original logic was flawed.")]]
    uint64_t ring_oscillator (uint64_t number_of_not_gates, uint64_t number_of_shift_registers, uint64_t number_of_xor_gates, char shift_direction_char, int digital_signal)
    {
        ShiftDirection dir;
        if (shift_direction_char == 'L' || shift_direction_char == 'l') {
            dir = ShiftDirection::LEFT;
        } else if (shift_direction_char == 'R' || shift_direction_char == 'r') {
            dir = ShiftDirection::RIGHT;
        } else {
             // Or handle error appropriately
            throw std::invalid_argument("Invalid shift direction character");
        }

        // Be careful with casting int to uint64_t - assuming non-negative seed intention
        uint64_t seed = (digital_signal >= 0) ? static_cast<uint64_t>(digital_signal) : 0;

        // Call the corrected and optimized static function
        // Note: Making the new function static means this wrapper doesn't need to be static,
        // but if rngs has no state, the whole class might be better as namespace functions.
        return simulate_bitwise_sequence(number_of_not_gates, number_of_shift_registers, number_of_xor_gates, dir, seed);
    }

}; // end class rngs
