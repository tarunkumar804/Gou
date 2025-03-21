class numerical_methods{
    public:

        uint8192_t compute_e (uint8192_t precision)
        {
            //Computes Euler's constant to a the precision specified.
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
           int8192_t integer_result = 1, fractional_result = 1;

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

        double return_limit_result(double point){
            /** Explanation:
             *  Lim(variable -> point) = f(variable).
             *  In this case, variable would be equal to the point in the curve or line.
             *  Lim (variable -> point) means the curve is going to an infinitisemally small value, it might as well be the point in the curve or line.
             */
            return point;
        }

        double8192_t inverse_exponentiation (double8192_t number, double8192_t root_of, double8192_t precision)
        {
            //Computes roots of number with any root.
           double8192_t root = number/root_of;
           int8192_t integer_part = number;
           float8192_t fractional_part = integer_part - number;

           for (int8192_t i = 0; i <= precision; i++)
                 root = root/root_of;
           while ((integer_part - fractional_part) > 0)
           {
               fractional_part = fractional_part * 10;
               root = root/root_of;
           }

           return root;
        }

        double evaluate_function(string expression, double point){
            double result = 0;
            return result;
        }

        double single_variable_limit(double point, string expression){
            /**  Function explanation:
            * Lim (variable -> point) (f(variable)) = f(point)  
            */

            double result = evaluate_function(expression, point);
            return result;
        }

        double single_variable_integration(string expression, double point, double margin_of_error, double precision){

            /**Explanation of function
             * Evaluates the infinitismally small value of the function and then, adds them up.
             */

            double differentiation_result = single_variable_differentiation(margin_of_error, point, expression);
            long single_variable_integration_result = 0;
            int precision_integer = 0;

            if (precision < 0)
                precision_integer = (-1) * (precision);
            else if (precision > 0)
                precision_integer = precision;

            for (int i = 0; i < precision; i++)
                single_variable_integration_result = single_variable_integration_result + differentiation_result;
            return single_variable_integration_result;
        }

        double multivariable_integration(string expression1, string expression2, double x_point1, double x_point2, double y_point1, double y_point2, double margin_of_error_point1, double margin_of_error_point2, double dx_precision, double dy_precision){
            /** Explanation of below statements:
            * Integration is analogus to addtion.
            * Differentiation is analogus to subtraction.
            * When intgeration is done, limits are the ones that are being evaluated.
            * Evaluate the functions with respect to those limits.
            * Is prone to error.
            */

            double dy1 = evaluate_function(expression2, y_point1);
            double dy2 = evaluate_function(expression2, y_point2);
            double dx1 = evaluate_function(expression1, x_point1);
            double dx2 = evaluate_function(expression2, x_point2);

            double multivariable_integration_result = (dy2 - dy1) * (dx2 - dx1);

            return multivariable_integration_result;
        }

        double single_variable_differentiation (double margin_of_error, double point, string expression){
            double differentiation_result = (evaluate_function(expression, point+margin_of_error) - evaluate_function(expression, margin_of_error))/ evaluate_function (expression, margin_of_error);
            return differentiation_result;
        }
};