class fv{
    double single_payment(double principal, float rate_of_interest, long long int payment_periods)
    {
        double fv = 0;
        rate_of_interest = 1 + rate_of_interest;
        for (long long int iteration = 0; iteration < payment_periods; iteration++)
            rate_of_interest = rate_of_interest * rate_of_interest;
        fv = principal * rate_of_interest;
        return fv;
    }
};