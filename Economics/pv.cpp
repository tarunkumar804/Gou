class pv{
    public:
        
        uint8192_t single_payment_present_amount (uint8192_t future_value, uint8192_t rate_of_interest, uint8192_t payment_periods)
        {
            double pv = 0;
            
            rate_of_interest = (1+rate_of_interest);
            for (uint8192_t iteration = 0; iteration <= payment_periods; iteration++)
                rate_of_interest = rate_of_interest * rate_of_interest;
            pv = future_value/rate_of_interest;

            return pv;
        }

        uint8192_t* periodic_payments_present_amount (uint8192_t future_amount, uint8192_t rate_of_interest, uint8192_t payment_periods)
        {
            uint8192_t temporary_copy = rate_of_interest;
            rate_of_interest = (1 + rate_of_interest);

            uint8192_t periodic_payments[periodic_payments];

            for (uint8192_t payment = 0; payment < payment_periods; payment++)
            {
                for (uint8192_t compounding = 0; compounding < payment; compounding++)
                    rate_of_interest = (rate_of_interest * rate_of_interest);
                periodic_payments[payment] = (future_amount * temporary_copy)/(rate_of_interest - 1);
            }

            return periodic_payments;
        }
        
        uint8192_t present_value_of_arithmetic_gradient_series()
        {
            
        }
};