#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cstdint>
#include <limits>

using double8192_t = __float128; // High-precision floating-point type (platform-dependent)

class number_theory {
public:
    // **Gauss Sum**: Computes the sum of the first n natural numbers
    double gauss_sum(int n) {
        if (n < 0) throw std::invalid_argument("n must be non-negative");
        return static_cast<double>(n) * (n + 1) / 2;
    }

    // **Factorial**: Computes n! with memoization for efficiency
    double8192_t factorial(double8192_t n) {
        if (n < 0) throw std::invalid_argument("Factorial is not defined for negative numbers");
        if (n == 0 || n == 1) return 1;
        static std::vector<double8192_t> memo = {1, 1}; // Memoization cache
        if (n < memo.size()) return memo[n];
        for (double8192_t i = memo.size(); i <= n; ++i) {
            memo.push_back(i * memo[i - 1]);
        }
        return memo[n];
    }

    // **Combination**: Computes n choose r (nCr)
    double8192_t combination(double8192_t n, double8192_t r) {
        if (r < 0 || r > n) throw std::invalid_argument("r must be between 0 and n");
        double8192_t n_fact = factorial(n);
        double8192_t n_r_fact = factorial(n - r);
        double8192_t r_fact = factorial(r);
        return n_fact / (n_r_fact * r_fact);
    }

    // **Permutation**: Computes n permute r (nPr)
    double8192_t permutation(double8192_t n, double8192_t r) {
        if (r < 0 || r > n) throw std::invalid_argument("r must be between 0 and n");
        double8192_t n_fact = factorial(n);
        double8192_t n_r_fact = factorial(n - r);
        return n_fact / n_r_fact;
    }

    // **Divisibility Theorem**: Computes quotient and remainder (a = q*b + r)
    std::pair<double, double> divisibility_theorem(double a, double b, long iterations) {
        if (b == 0) throw std::invalid_argument("Division by zero");
        double q = 0, r = a;
        for (long l = 0; l < iterations; ++l) {
            q = std::floor(a / b);
            r = a - q * b;
            a = b;
            b = r;
            if (b == 0) break; // Early termination if remainder is zero
        }
        return {q, r};
    }

    // **GCD**: Greatest Common Divisor using Euclidean algorithm
    double8192_t gcd(double8192_t a, double8192_t b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            double8192_t temp = b;
            b = std::fmod(a, b);
            a = temp;
        }
        return a;
    }

    // **LCM**: Least Common Multiple using GCD
    double8192_t lcm(double8192_t a, double8192_t b) {
        if (a == 0 || b == 0) return 0;
        return std::abs(a * b) / gcd(a, b);
    }

    // **Is Prime**: Checks if a number is prime
    bool is_prime(long long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (long long i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // **Prime Factorization**: Returns prime factors with their multiplicities
    std::vector<std::pair<long long, int>> prime_factors(long long n) {
        if (n <= 1) return {};
        std::vector<std::pair<long long, int>> factors;
        while (n % 2 == 0) {
            int count = 0;
            do {
                count++;
                n /= 2;
            } while (n % 2 == 0);
            factors.push_back({2, count});
        }
        for (long long i = 3; i <= std::sqrt(n); i += 2) {
            int count = 0;
            while (n % i == 0) {
                count++;
                n /= i;
            }
            if (count > 0) factors.push_back({i, count});
        }
        if (n > 2) factors.push_back({n, 1});
        return factors;
    }

    // **Modular Inverse**: Computes the modular inverse using Extended Euclidean Algorithm
    long long mod_inverse(long long a, long long m) {
        long long m0 = m, t, q;
        long long x0 = 0, x1 = 1;
        if (m == 1) return 0;
        while (a > 1) {
            q = a / m;
            t = m;
            m = a % m;
            a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        if (gcd(a, m0) != 1) throw std::invalid_argument("Modular inverse does not exist");
        return x1;
    }

    // **Chinese Remainder Theorem**: Solves a system of congruences
    long long chinese_remainder(const std::vector<long long>& a, const std::vector<long long>& m) {
        if (a.size() != m.size()) throw std::invalid_argument("Mismatch in remainder and moduli sizes");
        long long prod = 1;
        for (auto mi : m) prod *= mi;
        long long sum = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            long long p = prod / m[i];
            sum += a[i] * mod_inverse(p, m[i]) * p;
        }
        return sum % prod;
    }
};

