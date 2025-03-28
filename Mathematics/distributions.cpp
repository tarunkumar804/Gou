class binomial_distribution{
    public:
        double* pmf (long long int number_of_trials, double set[])
        {
            /** A function to calculate the pmfs of the given set.
            *  @param number_of_trials - number of times the trial needs to be done.
            *  @param set - the data set.
            *  @return An array containing the pmfs for each of the values.
            */

            double pmfs [number_of_trials], ncr = 0;
            float p[sizeof(set)], q[sizeof(set)];
            long long int trial = 0, count = 0;

            while (trial <= number_of_trials)
            {
                for (int i = 0; i < sizeof(set); i++)
                {
                    for (int j = 0; j < sizeof(set); j++)
                        if (set[i] == set[j])
                            count ++;
                    p[i] = count/sizeof(set);
                    q[i] = 1 - p[i];
                    count = 0;
                }

                for (int i = 0; i < sizeof(set); i++)
                {
                    for (int j = 0; j < sizeof(set); j++)
                        p[i] = p [i] * p [i]; // Calculates p ^ k
                    for (int j = i; j < sizeof(set); j++)
                        q[i] = q[i] * q[i]; // Calculates q ^ (n-k)

                    ncr = combination(sizeof(set), i); // combination (n, i)
                    
                    pmfs [i] = ncr * p[i] * q[i];
                }
            }

            return pmfs;
        }

        double* expectation (double set[])
        {
            /** A function to calculate expectations from the given set.
            *  @param set - The data set.
            *  @return A set containing expectation values.
            */

            double expectations [sizeof(set)], p;
            long long int count = 0;

            for (int i = 0; i < sizeof(set); i++)
            {
                for (int j = 0; j < sizeof(set); j++)
                {
                    if (set[i] == set[j])
                        count ++;
                }

                p = count/sizeof(set);
                expectations[i] = p * sizeof(set);
                count = 0;
            }

            return expectations;
        }

        double* variance (double set[])
        {
            /** A function to calculate 
            * @param set - The data set.
            * @return An array containing variances.
            */

            double variances[sizeof(set)], p, q;
            long long int count = 0;

            for (int i = 0; i < sizeof(set); i++)
            {
                for (int j = 0; j < sizeof(set); j++)
                    if (set[i] == set[j])
                        count++;
                
                p = count/sizeof(set);
                q = 1 - p;

                variances[i] = sizeof(set)*p*q;
            }

            return variances;
        }

        double* skewness (double set[])
        {
            /** A function to calculate skewness.
            * @param set - the data set.
            * @return An array containing the skewness of the data set.
            */

            double p = 0, q = 0, npq_root = 0, skewness[sizeof(set)];
            long long int count = 0;

            for (int i = 0; i < sizeof(set); i++)
            {
                for (int j = 0; j < sizeof(set); j++)
                {
                    if (set[i] == set[j])
                        count++;
                }

                p = count/sizeof(set);
                q = 1 - p;

                npq_root = (sizeof(set) * p * q);
                npq_root = npq_root/2;
                skewness[i] = (q-p)/npq_root;
            }

            return skewness;
        }

        double* excess_kutosis (double set[])
        {
            double excess_kurtosis[sizeof(set)], p = 0, q = 0;
            long long int count = 0;

            for (int i = 0; i < sizeof(set); i++)
            {
                for (int j = 0; j < sizeof(set); j++)
                    if (set[i] == set[j])
                        count++;

                p = count/sizeof(set);
                q = 1 - p;

                excess_kurtosis[i] = (1 - (6 *p *q))/(sizeof(set)*p*q);
            }

            return excess_kurtosis;
        }
};