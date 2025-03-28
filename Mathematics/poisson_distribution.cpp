#include <cmath>
#include <vector>
#include <cstdint>
#include <stdexcept>

class poisson_distribution {
public:
    // Constructor: Initialize with rate parameter (lambda)
    poisson_distribution(double lambda) : lambda_(lambda) {
        if (lambda <= 0.0) {
            throw std::invalid_argument("Lambda must be positive.");
        }
    }

    // Probability Mass Function: P(X = k)
    double pmf(uint64_t k) const {
        // Use log form to avoid overflow: ln(P) = k*ln(lambda) - lambda - ln(k!)
        double log_pmf = static_cast<double>(k) * std::log(lambda_) - lambda_ - std::lgamma(k + 1);
        return std::exp(log_pmf);
    }

    // Cumulative Distribution Function: P(X <= k)
    double cdf(uint64_t k) const {
        double sum = 0.0;
        for (uint64_t i = 0; i <= k; ++i) {
            sum += pmf(i);
        }
        return sum;
    }

    // Mean: lambda
    double mean() const {
        return lambda_;
    }

    // Variance: lambda
    double variance() const {
        return lambda_;
    }

    // Skewness: 1 / sqrt(lambda)
    double skewness() const {
        return 1.0 / std::sqrt(lambda_);
    }

    // Excess Kurtosis: 1 / lambda
    double excess_kurtosis() const {
        return 1.0 / lambda_;
    }

    // Full Kurtosis: 3 + excess kurtosis
    double kurtosis() const {
        return 3.0 + excess_kurtosis();
    }

    // Generate a vector of PMF values for k = 0 to k_max
    std::vector<double> pmf_vector(uint64_t k_max) const {
        std::vector<double> result(k_max + 1);
        for (uint64_t k = 0; k <= k_max; ++k) {
            result[k] = pmf(k);
        }
        return result;
    }

private:
    //Question : Shouldn't you declare this before public?
    double lambda_; // Rate parameter
};
