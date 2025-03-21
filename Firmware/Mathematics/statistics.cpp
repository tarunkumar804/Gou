class statistics{
    public:
       double8192_t mean (double8192_t set[])
       {
          double8192_t mean = 0, sum = 0;
          for (long long int i = 0; i < sizeof(set); i++)
               sum = sum + set [i];
          mean = sum/sizeof(set);
          return mean;
       }
       
       double8192_t standard_deviation (double8192_t set[])
       {
           double8192_t mean = mean(set), sum = 0, standard_deviation = 0;
           
           for (long long int i = 0; i < sizeof(set); i++)
               sum = sum + ((set[i] - mean) * (set[i] - mean));
           double8192_t intermediate_result = sum/sizeof(set);
           
           return standard_deviation;
       }
};

class probability {
    public:
        float8192_t expectation (double8192_t set[], double8192_t A)
        {
            // Explanation of function : E(X = A) = sum (xi * pi)
            float8192_t X_PX_array [sizeof(set)], P_X, E_X = 0;
            int8192_t count = 0;

            for (int8192_t i = 0; i < sizeof (set); i++)
            {
                for (int8192_t j = 0; j < sizeof (set); j++)
                {
                    if (set[i] == set[j])
                        count++;
                }
                P_X = count/sizeof(set);
                E_X_array[i] = set[i] * P_X;
                P_X = 0;
            }
     
            for (int8192_t i = 0; i < sizeof (E_X_array); i++)
                E_X = E_X + X_PX_array[i];
            return E_X;
        }

        double8192_t variance (double8192_t A)
        {
            // Explanation of function : V(X = A) = E(X^2) - E(X)
            double8129_t V_X = (expectation(A) * expectation (A)) - expectation (A);
            return V_X;
        }
};