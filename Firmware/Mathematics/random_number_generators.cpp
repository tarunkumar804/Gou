#include <vector>
#include <cstdint>
#include <random>
#include <string>

// A class to simulate a single ring oscillator
class RingOscillator {
private:
    std::vector<uint8_t> state; // State of each "gate" (0 or 1)
    size_t size;                // Number of gates in the ring

public:
    // Constructor: initialize with a given number of gates and random state
    RingOscillator(size_t num_gates, std::mt19937& rng) 
        : size(num_gates), state(num_gates) {
        std::bernoulli_distribution dist(0.5); // 50% chance of 0 or 1
        for (auto& bit : state) {
            bit = dist(rng) ? 1 : 0; // Randomly initialize each bit
        }
    }

    // Step the oscillator: update state based on the ring topology
    void step() {
        std::vector<uint8_t> next_state(size);
        for (size_t i = 0; i < size; ++i) {
            // Each gate's new state is the inverse of the next gate's current state
            next_state[i] = 1 - state[(i + 1) % size];
        }
        state = std::move(next_state); // Efficiently update the state
    }

    // Get the output bit (from the last gate)
    uint8_t get_output() const {
        return state.back();
    }
};

// Enhanced RNG class
class rng {
private:
    std::vector<RingOscillator> oscillators; // Multiple ring oscillators
    std::mt19937 prng;                       // Mersenne Twister PRNG for initialization

public:
    // Constructor: initialize with 8 oscillators of different sizes
    rng() : prng(std::random_device{}()) {
        // Use odd prime numbers for oscillator sizes to ensure diverse periods
        std::vector<size_t> primes = {3, 5, 7, 11, 13, 17, 19, 23};
        for (size_t p : primes) {
            oscillators.emplace_back(p, prng); // Create each oscillator
        }
    }

    // Generate a single random byte using all oscillators
    uint8_t generate_byte() {
        // Step all oscillators once
        for (auto& osc : oscillators) {
            osc.step();
        }
        // Combine outputs of all 8 oscillators into one byte
        uint8_t byte = 0;
        for (size_t i = 0; i < 8; ++i) {
            byte |= (oscillators[i].get_output() << i);
        }
        return byte;
    }

    // Generate a stream of random bytes
    std::string generate_stream(size_t num_bytes) {
        std::string stream;
        stream.reserve(num_bytes); // Pre-allocate for efficiency
        for (size_t i = 0; i < num_bytes; ++i) {
            stream.push_back(static_cast<char>(generate_byte()));
        }
        return stream;
    }

    // Optional: Generate a stream with a custom seed for reproducibility
    std::string generate_stream(size_t num_bytes, unsigned seed) {
        prng.seed(seed);
        // Reinitialize oscillator states with the new seed
        oscillators.clear();
        std::vector<size_t> primes = {3, 5, 7, 11, 13, 17, 19, 23};
        for (size_t p : primes) {
            oscillators.emplace_back(p, prng);
        }
        return generate_stream(num_bytes);
    }
};
