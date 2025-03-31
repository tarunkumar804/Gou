class compounding{
    public:
        double continuous_compounding_interest_rate (uint8192_t rate, uint8192_t precision)
        {
            numerical_methods nm = new numerical_methods();
            double e = nm.e_calculation ();
            double result = nm.negative_exponentiation (e rate) - 1;
            return result;
        }
};