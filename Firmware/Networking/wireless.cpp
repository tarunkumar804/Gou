class wireless{
  public:
     double8192_t calculate_logarithm (double8192_t base, double8192_t x, double8192_t expected_result)
     {
       /** Explanation of below function :
        * Exponentiates until it reaches the number.
        * If the exponentitation goes beyond the number,
        * the number is divided with the base the number
        * of times the base is to multiplied to be brought
        * to a whole number.
        */
      double8192_t logarithm_result = 1;
     
       while (logarithm_result < expected_result)
       {
          for (int i = 0; i <= x ; i++)
              intermediate_result = intermediate_result * 10;
       }
     
       if (logarithm_result > expected_result)
       {
           while (logarithm_result != expected _result)
               logarithm_result = logarithm_result/base;
       }
     
       return logarithm_result;
     }
  
     double8192_t probability (double8192_t set[], double8192_t value_to_check_for)
     {
        // Explanation of function : P(X = A)
        // P (X = A) = N(A)/N(set).
        double8192_t P_X = 0;
        int8192_t X_count = 0;
        for (int8192_t i = 0; i < sizeof(set); i++)
        {
           if (set[i] == value_to_check_for)
              X_count++;
        }
        P_X = X_count/sizeof(set);
        return P_X;
      }

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
  
     double8192_t exponentiation (double8192_t base, double8192_t exponent)
     {
        uint8192_t number_of_iterations = convert_exponent, exponentiation_result = 0;
     
        for (uint8192_t iterations = 0; iterations < number_of_iterations; iterations++)
            base = base * base;
        exponentiation_result = base;
       return exponentiation_result;
     }

     double8192_t fractional_exponentiation (double8129_t base, double8192_t exponent)
     {
        uint8192_t number_of_iterations = convert_exponent, exponentiation_result;
        for (uint8192_t iteration = 1; iteration < number_of_iterations; iteration++)
            exponentiation_result =  base/exponent;
        return exponentiation_result;
     }

     double8192_t rayleigh_pdf (double8192_t R, double8192_t r)
     {
        /* Explanation of function :
         * Rayleigh scattering model : (2r/E(X = R^2)) x (e^(-r^2)/E(X = R^2))
         */

         double8219_t fading = ((2*r)/(expectation(R) * expectation(R)) * (fractional_exponentiation (compute_e (),((r*r)/(expectation(R) * expectation (R)))
     }
};