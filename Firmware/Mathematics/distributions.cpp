#include <cmath>
#include <vector>
#include <cstdint>
#include <stdexcept>

class binomial_distribution {
public:
    // Constructor: Initialize with number of trials (n) and probability of success (p)
    binomial_distribution(uint64_t n, double p) : n_(n), p_(p) {
        if (p < 0.0 || p > 1.0) {
            throw std::invalid_argument("Probability p must be between 0 and 1.");
        }
    }

    // Probability Mass Function: P(X = k)
    double pmf(uint64_t k) const {
        if (k > n_) return 0.0;
        double coeff = binom_coeff(n_, k);
        return coeff * std::pow(p_, static_cast<double>(k)) * std::pow(1.0 - p_, static_cast<double>(n_ - k));
    }

    // Cumulative Distribution Function: P(X <= k)
    double cdf(uint64_t k) const {
        if (k >= n_) return 1.0;
        double sum = 0.0;
        for (uint64_t i = 0; i <= k; ++i) {
            sum += pmf(i);
        }
        return sum;
    }

    // Mean: n * p
    double mean() const {
        return static_cast<double>(n_) * p_;
    }

    // Variance: n * p * (1 - p)
    double variance() const {
        return static_cast<double>(n_) * p_ * (1.0 - p_);
    }

    // Skewness: (1 - 2p) / sqrt(n * p * (1 - p))
    double skewness() const {
        return (1.0 - 2.0 * p_) / std::sqrt(static_cast<double>(n_) * p_ * (1.0 - p_));
    }

    // Excess Kurtosis: (1 - 6p(1 - p)) / (n * p * (1 - p))
    double excess_kurtosis() const {
        return (1.0 - 6.0 * p_ * (1.0 - p_)) / (static_cast<double>(n_) * p_ * (1.0 - p_));
    }

    // Full Kurtosis: 3 + excess kurtosis
    double kurtosis() const {
        return 3.0 + excess_kurtosis();
    }

    // Generate a vector of PMF values for k = 0 to n
    std::vector<double> pmf_vector() const {
        std::vector<double> result(n_ + 1);
        for (uint64_t k = 0; k <= n_; ++k) {
            result[k] = pmf(k);
        }
        return result;
    }

private:
    uint64_t n_; // Number of trials
    double p_;   // Probability of success

    // Binomial coefficient: n choose k
    double binom_coeff(uint64_t n, uint64_t k) const {
        if (k > n) return 0.0;
        double result = 1.0;
        k = std::min(k, n - k); // Optimize by using symmetry
        for (uint64_t i = 1; i <= k; ++i) {
            result *= static_cast<double>(n - k + i) / static_cast<double>(i);
        }
        return result;
    }
};
