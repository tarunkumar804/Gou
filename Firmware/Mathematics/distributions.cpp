class binomial_distribution{
    public:
        double* pmf (double set[], double value_to_search_for, long number_of_iteraions)
        {
            long count = 0, ncr = 1, p = 1, q = 0, iteration = 0;
            double result[sizeof(set)];

            do{
                if (iteration == 0)
                {
                    q = 1-p;

                    for (long l = 0; l < sizeof(set) - iteration; l++)
                        q = q * q;
                    result[iteration] = 1 * p * q;
                }

                else if (iteration > 0)
                {
                    for (long l = 0; l < sizeof(set); l++)
                        if (set[l] == value_to_search_for)
                            count++;
                    p = count/sizeof(set);
                    q = 1 - p;

                    for (long l = 0; l < iteration; l++)
                        p = p * p;
                    for (long l = 0; l < sizeof(set) - iteration; l++)
                        q = q * q;
                    ncr = combination(number_of_iteraions, iteration);
                    result [iteration] = ncr * p * q;
                }

                iteration ++;

            }while(iteration < number_of_iteraions);

            return result;
        }

        double mean (double set[], double value_to_search_for)
        {
            long count = 0;
            double p = 0, mean = 0;

            for (long l = 0; l < sizeof(set); l++)
                if (set[l] == value_to_search_for)
                    count++;

            p = count/sizeof(set);

            return mean;
        }

        double variance (double set[], double value_to_search_for)
        {
            long count = 0;
            double p = 0, q = 0, variance = 0;

            for (long l = 0; l < sizeof(set); l++)
                if (set[l] == value_to_search_for)
                    count ++;
            p = count/sizeof(set);
            q = 1 - p;
            variance = sizeof(set) * p * q;

            return variance;
        }
};

class poisson_distribtuion{
    protected:
        double8192_t e;

    public:
        poisson_distribtuion(uint8192_t precision)
        {
            e = e_calculation(precision);
        }

        double8192_t pmf (double8192_t lambda, double8192_t k)
        {
            
        } 
};