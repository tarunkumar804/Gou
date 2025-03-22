#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <map>

class statistics {
public:
    // Mean: Arithmetic average of the set
    double mean(const std::vector<double>& set) const {
        if (set.empty()) {
            throw std::invalid_argument("Cannot compute mean of an empty set.");
        }
        double sum = 0.0;
        for (const auto& val : set) {
            sum += val;
        }
        return sum / static_cast<double>(set.size());
    }

    // Standard Deviation: Sample standard deviation
    double standard_deviation(const std::vector<double>& set) const {
        if (set.size() < 2) {
            throw std::invalid_argument("Standard deviation requires at least two elements.");
        }
        double mu = mean(set);
        double sum_sq_diff = 0.0;
        for (const auto& val : set) {
            double diff = val - mu;
            sum_sq_diff += diff * diff;
        }
        double variance = sum_sq_diff / static_cast<double>(set.size() - 1);
        return std::sqrt(variance);
    }

    // Variance: Sample variance
    double variance(const std::vector<double>& set) const {
        if (set.size() < 2) {
            throw std::invalid_argument("Variance requires at least two elements.");
        }
        double mu = mean(set);
        double sum_sq_diff = 0.0;
        for (const auto& val : set) {
            double diff = val - mu;
            sum_sq_diff += diff * diff;
        }
        return sum_sq_diff / static_cast<double>(set.size() - 1);
    }

    // Median: Middle value of the sorted set
    double median(std::vector<double> set) const {
        if (set.empty()) {
            throw std::invalid_argument("Cannot compute median of an empty set.");
        }
        std::sort(set.begin(), set.end());
        size_t n = set.size();
        if (n % 2 == 0) {
            return (set[n / 2 - 1] + set[n / 2]) / 2.0;
        } else {
            return set[n / 2];
        }
    }

    // Mode: Most frequent value(s) in the set
    std::vector<double> mode(const std::vector<double>& set) const {
        if (set.empty()) {
            throw std::invalid_argument("Cannot compute mode of an empty set.");
        }
        std::map<double, size_t> freq;
        for (const auto& val : set) {
            freq[val]++;
        }
        size_t max_count = 0;
        for (const auto& pair : freq) {
            max_count = std::max(max_count, pair.second);
        }
        std::vector<double> modes;
        for (const auto& pair : freq) {
            if (pair.second == max_count) {
                modes.push_back(pair.first);
            }
        }
        return modes;
    }

    // Range: Difference between maximum and minimum values
    double range(const std::vector<double>& set) const {
        if (set.empty()) {
            throw std::invalid_argument("Cannot compute range of an empty set.");
        }
        auto [min_it, max_it] = std::minmax_element(set.begin(), set.end());
        return *max_it - *min_it;
    }

    // Skewness: Measure of the asymmetry of the distribution
    double skewness(const std::vector<double>& set) const {
        if (set.size() < 3) {
            throw std::invalid_argument("Skewness requires at least three elements.");
        }
        double mu = mean(set);
        double sum_cubed_diff = 0.0;
        double sum_sq_diff = 0.0;
        for (const auto& val : set) {
            double diff = val - mu;
            sum_cubed_diff += diff * diff * diff;
            sum_sq_diff += diff * diff;
        }
        double n = static_cast<double>(set.size());
        double m3 = sum_cubed_diff / n;
        double m2 = sum_sq_diff / n;
        return (m3 / std::pow(m2, 1.5)) * (n / (n - 1) / (n - 2));
    }

    // Kurtosis: Measure of the "tailedness" of the distribution
    double kurtosis(const std::vector<double>& set) const {
        if (set.size() < 4) {
            throw std::invalid_argument("Kurtosis requires at least four elements.");
        }
        double mu = mean(set);
        double sum_fourth_diff = 0.0;
        double sum_sq_diff = 0.0;
        for (const auto& val : set) {
            double diff = val - mu;
            sum_fourth_diff += diff * diff * diff * diff;
            sum_sq_diff += diff * diff;
        }
        double n = static_cast<double>(set.size());
        double m4 = sum_fourth_diff / n;
        double m2 = sum_sq_diff / n;
        return (m4 / (m2 * m2)) * (n * (n + 1) / ((n - 1) * (n - 2) * (n - 3))) -
               3.0 * (n - 1) * (n - 1) / ((n - 2) * (n - 3));
    }
};
