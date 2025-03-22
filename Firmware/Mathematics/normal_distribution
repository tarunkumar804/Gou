#include <cmath>
#include <stdexcept>

class normal_distribution {
public:
    // Constructor: Initialize with mean (mu) and standard deviation (sigma)
    normal_distribution(double mean, double stddev) : mean_(mean), stddev_(stddev) {
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

private:
    double mean_;   // Mean (mu)
    double stddev_; // Standard deviation (sigma)
