class fv{
    double single_payment(double principal, float rate_of_interest, long long int payment_periods)
    {
        /** A function to calculate future value of a single amount.
        * @param principal - Initial amount of the series.
        * @param rate_of_interest - Interest rate in percentage.
        * @param payment_periods - Number of payment periods.
        * @return Future value of a single payment.
        */

        double fv = 0;
        rate_of_interest = 1 + rate_of_interest;
        for (long long int payment = 0; payment < payment_periods; payment++)
            rate_of_interest = rate_of_interest * rate_of_interest;
        fv = principal * rate_of_interest;
        return fv;
    }

    double annual_payments (double *annuities, float rate_of_interest, long long int payment_periods)
    {
        /** A function to calculate future value of annuities.
        * @param annuities - An array of periodic payments.
        * @param rate_of_interest - Rate of interest in percentages.
        * @param payment_periods - Number of payment periods.
        * @return future value.
        */

        double fv = 0;
        float interest_copy = 1 + rate_of_interest;

        for (long long int payment = 0; payment < payment_periods; payment++)
            fv = fv + annuities[payment] * (((interest_copy * interest_copy) - 1)/rate_of_interest);
        return fv;
    }
};