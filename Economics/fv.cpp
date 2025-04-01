class fv{
    double single_payment(double principal, float rate_of_interest, long long int payment_periods){
        /** A function to calculate future value of a single amount.
        * @authors Tarun Kumar, Leonardo Di Maximillian.
        * @param principal - Initial amount of the series.
        * @param rate_of_interest - Interest rate in percentage.
        * @param payment_periods - Number of payment periods.
        * @return Future value of a single payment.
        * Implements the equation : F = P + P(1+r)^n
        */

        double fv = 0, rate_of_interest_copy = rate_of_interest;

        rate_of_interest_copy = 1 + rate_of_interest;
        for (long long int payment = 0; payment < payment_periods; payment++)
            rate_of_interest_copy = rate_of_interest_copy * rate_of_interest_copy;
        fv = principal + (principal * rate_of_interest);
        return fv;
    }

    double annual_payments (double *annuities, float rate_of_interest, long long int payment_periods){
        /** A function to calculate future value of annuities.
        * @authors Tarun Kumar, Leonardo Di Maximillian.
        * @param annuities - An array of periodic payments.
        * @param rate_of_interest - Rate of interest in percentages.
        * @param payment_periods - Number of payment periods.
        * @return annual payments.
        * Implements the equation : F = A *((1+i)^n - 1/i)
        */

        double fv  = 0;
        float interest_copy = 1 + rate_of_interest;

        for (long long int payment = 0; payment < payment_periods; payment++)
            fv = fv + annuities[payment] * (((interest_copy * interest_copy) - 1)/rate_of_interest); //Adds all the annuities after calculating the compounding factor.
        return fv;
    }
};