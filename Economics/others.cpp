class others{
    public:
        double continuous_compounding (double annuity, double interest_rate)
        {
            /** Implements the equation
            * F = A/i.
            * @param periodic_payment - The annuity.
            * @param interest_rate - The continuous interest rate.
            * @return Future value of the continuous annuity.
            */

            double value = annuity/interest_rate;
            return value;
        }    
};