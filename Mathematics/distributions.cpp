class binomial_distribution{
    public:
        double* pmf (long long int number_of_trials, double set[])
        {
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
        }
};