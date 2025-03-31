#include <cmath> // For std::pow

class fv {
public:
    double single_payment(double principal, double rate_of_interest, long long int payment_periods) {
        /**
         * Calculates the future value of a single amount using compound interest.
         * @param principal Initial amount.
         * @param rate_of_interest Interest rate in decimal form (e.g., 0.05 for 5%).
         * @param payment_periods Number of compounding periods.
         * @return Future value of the single payment.
         */
        if (payment_periods < 0) {
            throw std::invalid_argument("Payment periods cannot be negative.");
        }
        double rate_multiplier = 1.0 + rate_of_interest;
        double future_value = principal * std::pow(rate_multiplier, payment_periods);
        return future_value;
    }

    double annual_payments(const double* annuities, double rate_of_interest, long long int payment_periods) {
        /**
         * Calculates the future value of a series of periodic payments (annuities).
         * @param annuities Array of periodic payments.
         * @param rate_of_interest Interest rate in decimal form (e.g., 0.05 for 5%).
         * @param payment_periods Number of payment periods.
         * @return Future value of the annuities.
         */
        if (payment_periods < 0) {
            throw std::invalid_argument("Payment periods cannot be negative.");
        }
        double future_value = 0.0;
        double rate_multiplier = 1.0 + rate_of_interest;
        for (long long int t = 0; t < payment_periods; ++t) {
            // Future value of payment at time t: annuity[t] * (1 + rate)^(n - t - 1)
            double periods_remaining = payment_periods - t - 1;
            future_value += annuities[t] * std::pow(rate_multiplier, periods_remaining);
        }
        return future_value;
    }
};
