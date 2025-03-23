#include <cmath>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <random>

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

    // Approximate CDF using normal distribution with continuity correction
    double approx_cdf(uint64_t k) const {
        double mu = static_cast<double>(n_) * p_;
        double sigma = std::sqrt(static_cast<double>(n_) * p_ * (1.0 - p_));
        if (sigma == 0.0) {
            if (n_ == 0 || p_ == 0.0) {
                return 1.0; // Degenerate at 0
            } else { // p_ == 1.0 and n_ > 0
                return (k >= n_) ? 1.0 : 0.0; // Degenerate at n_
            }
        }
        double z = (static_cast<double>(k) + 0.5 - mu) / sigma;
        return normal_cdf(z);
    }

    // Quantile function: smallest k such that P(X <= k) >= prob
    uint64_t quantile(double prob) const {
        if (prob < 0.0 || prob > 1.0) {
            throw std::invalid_argument("Probability must be between 0 and 1.");
        }
        if (prob == 0.0) return 0;
        if (prob == 1.0) return n_;
        uint64_t low = 0;
        uint64_t high = n_;
        while (low < high) {
            uint64_t mid = low + (high - low) / 2;
            double cdf_mid = cdf(mid);
            if (cdf_mid < prob) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }

    // Generate a random sample from the binomial distribution
    uint64_t sample(std::mt19937& gen) const {
        uint64_t sum = 0;
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        for (uint64_t i = 0; i < n_; ++i) {
            if (dist(gen) < p_) sum++;
        }
        return sum;
    }

    // Compute the mode(s) of the distribution
    std::vector<uint64_t> modes() const {
        double m = (n_ + 1) * p_;
        if (std::floor(m) == m) { // m is an integer
            uint64_t k = static_cast<uint64_t>(m);
            if (k == 0) {
                return {0};
            } else if (k == n_ + 1) {
                return {n_};
            } else {
                return {k - 1, k};
            }
        } else {
            uint64_t k = static_cast<uint64_t>(std::floor(m));
            return {k};
        }
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

    // Generate a vector of CDF values for k = 0 to n
    std::vector<double> cdf_vector() const {
        std::vector<double> result(n_ + 1);
        double sum = 0.0;
        for (uint64_t k = 0; k <= n_; ++k) {
            sum += pmf(k);
            result[k] = sum;
        }
        return result;
    }

    // Moment-Generating Function: (1 - p + p * e^t)^n
    double mgf(double t) const {
        return std::pow(1.0 - p_ + p_ * std::exp(t), static_cast<double>(n_));
    }

    // Entropy: -sum(p(k) * log(p(k)))
    double entropy() const {
        double sum = 0.0;
        for (uint64_t k = 0; k <= n_; ++k) {
            double p_k = pmf(k);
            if (p_k > 0.0) {
                sum += p_k * std::log(p_k);
            }
        }
        return -sum;
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

    // Standard normal CDF using erf
    double normal_cdf(double x) const {
        return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
    }
};
