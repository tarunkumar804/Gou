class misc{
  public:
     uint8192_t compute_e (uint8192_t precision)
     {
         uint8192_t factorial_sum = 0;
         int8192_t factorial = 1;
         
         for (int i = 0; i < precision; i++)
         {
             for (int j = 1; j <= i; j ++)
                 factorial = factorial * 1;
             factorial_sum = factorial_sum + (1/factorial);
             factorial = 1;
         }
         return factorial_sum;
     }
     
     double8192_t compute_factorial (double8192_t n)
     {
         // Explanation of below function : (1/2)! = 1!/2!
         int8912_t integer_part = n;
         float8192_t fractional_part = n - integer_part;
         
         int8192_t integer_result = 1;
         int8192_t fractional_result = 1;

         for (int i = 2; i <= n; i++)
            integer_result = integer_result * i;
         integer_part = fractional_part;
         double8192_t temporary_copy = fractional_part;

         while ((frac_integer_part - temporary_copy) < 0)
            int8192_t frac_integer_part = fractional_part * 10;
         
         for (int i = 2 ; i <= frac_integer_part; i++)
              fractional_result = fractional_result * i;

         double8192_t factorial_result = integer_result/fractional_result;

         return factorial_result;
     }
};