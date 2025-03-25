class binomial{
    public:
        double* pmfs (double set[], long number_of_trials)
        {
            double pmfs[sizeof(set)], P_X = 0, q = 0;
            long count = 0, n_factorial = 1, n_r_factorial = 1, ncr = 1, r_factorial = 1, trial = 0;

            for (long l = 1; l <= sizeof(set); l++)
                n_factorial = n_factorial * l;

            while (trial < number_of_trials)
            { //This seems very doubtful.
                for (long l = 0; l < sizeof(set); l++)
                {
                    for (long m = 0; m < sizeof(set); l++)
                        if (set[l] == set[m])
                            count ++;
                    P_X = count/sizeof(set);
                    q = 1 - P_X;
                }

                for (long l = 1 ; l <= sizeof(set) - trial; l++)
                {
                    n_r_factorial = n_r_factorial * l; //Calculates (n-r)!
                    q = q * q; // Calculates q ^ (n-x)
                }

                for (long l = 1; l <= trial; l++)
                {
                    r_factorial = r_factorial * l; // Calculates r!
                    P_X = P_X * P_X; // Calculates p ^ x
                }

                ncr = n_factorial/(n_r_factorial * r_factorial);

                pmfs[trial] = ncr * P_X * q;
                
                ncr = 1;
                n_factorial = 1;
                n_r_factorial = 1;
                r_factorial = 1;

                trial++; 
            }

            return pmfs;
        }

        double* expectations (double set[])
        {
            double mean_array[sizeof(set)], P_X = 0, q = 0;
            long count = 0;

            for (long l = 0; l < sizeof(set); l++)
            {
                for (long m = 0; m < sizeof(set); m++)
                    if (set[l] == set[m])
                        count ++;
                
                P_X = count/sizeof(set);

                mean_array [l] = sizeof(set) * P_X;
            }

            return mean_array;
        }

        double* variances (double set[])
        {
            double variances[sizeof(set)], P_X = 0, q = 0;
            long count = 0;

            for (long l = 0; l < sizeof(set); l++)
            {
                for (long m = 0; m < sizeof(set); m++)
                    if (set[l] == set[m])
                        count ++;
                P_X = count/sizeof(set);
                q = 1 - P_X;
                variances[l] = sizeof(set) * P_X * q;
            }

            return variances;
        }
};