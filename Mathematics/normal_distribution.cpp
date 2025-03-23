#include <cmath>
#include <stdexcept>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

class normal_distribution {
public:
    // Constructor: Initialize with mean (mu) and standard deviation (sigma)
    normal_distribution(double mean, double stddev)
        : mean_(mean), stddev_(stddev), generator_(std::random_device{}()) {
        if (stddev <= 0.0) {
            throw std::invalid_argument("Standard deviation must be positive.");
        }
    }

    // Probability Density Function: f(x)
    double pdf(double x) const {
        double z = (x - mean_) / stddev_;
        return (1.0 / (stddev_ * std::sqrt(2.0 * M_PI))) * std::exp(-0.5 * z * z);
    }

    // Cumulative Distribution Function: P(X <= x)
    double cdf(double x) const {
        double z = (x - mean_) / stddev_;
        return 0.5 * (1.0 + std::erf(z / std::sqrt(2.0)));
    }

    // Inverse CDF (Quantile Function): Finds x such that P(X <= x) = p
    double inv_cdf(double p) const {
        if (p <= 0.0 || p >= 1.0) {
            throw std::invalid_argument("p must be in (0,1)");
        }
        double z = std::sqrt(2.0) * std::erfinv(2.0 * p - 1.0);
        return mean_ + stddev_ * z;
    }

    // Mean: mu
    double mean() const {
        return mean_;
    }

    // Variance: sigma^2
    double variance() const {
        return stddev_ * stddev_;
    }

    // Skewness: 0 (symmetric distribution)
    double skewness() const {
        return 0.0;
    }

    // Excess Kurtosis: 0 (normal distribution)
    double excess_kurtosis() const {
        return 0.0;
    }

    // Full Kurtosis: 3 (normal distribution)
    double kurtosis() const {
        return 3.0;
    }

    // Generate a random sample from the distribution
    double random_sample() {
        std::normal_distribution<double> dist(mean_, stddev_);
        return dist(generator_);
    }

    // Generate multiple random samples
    std::vector<double> random_samples(size_t n) {
        std::vector<double> samples;
        samples.reserve(n);
        for (size_t i = 0; i < n; ++i) {
            samples.push_back(random_sample());
        }
        return samples;
    }

    // Log-Likelihood of a sample
    double log_likelihood(const std::vector<double>& data) const {
        if (data.empty()) return 0.0;
        double sum = 0.0;
        for (double x : data) {
            sum += std::log(pdf(x));
        }
        return sum;
    }

    // Maximum Likelihood Estimation (MLE) for mean and stddev from data
    static std::pair<double, double> mle(const std::vector<double>& data) {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty for MLE");
        }
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        double variance = 0.0;
        for (double x : data) {
            variance += (x - mean) * (x - mean);
        }
        variance /= data.size();
        return {mean, std::sqrt(variance)};
    }

    // Check if distribution parameters are valid
    bool is_valid() const {
        return stddev_ > 0.0 && std::isfinite(mean_) && std::isfinite(stddev_);
    }

private:
    double mean_;   // Mean (mu)
    double stddev_; // Standard deviation (sigma)
    std::mt19937 generator_; // Random number generator
};
