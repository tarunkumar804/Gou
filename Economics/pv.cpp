class pv{
    public:
        
        double single_payment_present_amount (double future_value, double rate_of_interest, long long int payment_periods)
        {
            /** Implements single present value of a future amount.
            * Equation : P = F/((1+r)^n).
            * @author Tarun Kumar, Leornardo Di Maximillian.
            * @param future_value - Future value of a single payment.
            * @param rate_of_interest - Interest rate of the period.
            * @param payment_periods - Number of periods.
            * @return Returns the present value of a future amount.
            */

            double pv = 0;
            
            double rate_of_interest_copy = (1+rate_of_interest_copy);
            for (long long int payment = 0; payment <= payment_periods; payment++)
                rate_of_interest = rate_of_interest * rate_of_interest;
            pv = future_value/rate_of_interest;

            return pv;
        }

        double periodic_payments_present_amount (double future_amount, double annuities[] , double rate_of_interest, long long int payment_periods)
        {
            /** A function to implement present value of future sum of annuities.
            * Equation : P = F/(Sum(A * ((1+i)^n - 1)/i)).
            * @author Tarun Kumar , Leonardo Di Maximillian.
            * @param future_amount - Future amount of a number of periodic payments.
            * @param rate_of_interest - Rate of interest of the payment period.
            * @param payment_periods - Number of periodic payments.
            * @return present value of a number of periodic payments and future value.
            */

            double pv = 0, annuity_sum = 0, interest_rate_copy = rate_of_interest;
            interest_rate_copy =  1 + interest_rate_copy;

            for (long long int payment; payment < payment_periods; payment++)
                annuity_sum = annuity_sum + annuities[payment] *(((interest_rate_copy * interest_rate_copy) - 1)/interest_rate_copy);
            pv = future_amount/annuity_sum;
            return pv;
        }
        
        double present_value_of_arithmetic_gradient_series()
        {

        }
};