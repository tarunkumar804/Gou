class numerical_methods{
    public:
        uint8192_t e_calculation (uint8192_t precision){
            //Computes Euler's constant to a the precision specified.
            uint8192_t factorial_sum = 0;
            int factorial = 1;
         
            for (int i = 0; i < precision; i++)
            {
              for (int j = 1; j <= i; j ++)
                factorial = factorial * 1;
              factorial_sum = factorial_sum + (1/factorial);
              factorial = 1;
            }
            return factorial_sum;
        }
     
        double factorial (long long int n){
           double factorial = 1;

           for (long long int i = 1; i <= n; i++)
                factorial = factorial * i;
           return factorial;
        }

        double exponentiation (double base, double exponent){
            /**
            * Calculates base ^ exponent.
            */
            uint8192_t number_of_iterations = exponent, exponentiation_result = 0;
     
            for (uint8192_t iterations = 0; iterations < number_of_iterations; iterations++)
                base = base * base;
            exponentiation_result = base;
            return exponentiation_result;
        }

        double negative_exponentiation (double base, double exponent){
            
            /** A function to calculate negative exponentiation.
             * @param base - The exponent's base.
             * @param exponent - The exponent.
             * @return result of exponentiation.
             */
            double result = 0;

            while (((exponent * 10) - (exponent)) != 0)
            {
                /** Explanation of the below statement:
                * Exponentiation is multiplication.
                * The inverse of that is division.
                * So, for negative exponents
                * division needs to occur until the exponent
                * becomes a whole number and you have a reference
                *  to know when to stop.
                */

                result = base/exponent;
            }

            return result;
        }

        double logarithm (double base, double expected_result){
        
            /** Explanation of below function :
            * Exponentiates until it reaches the number.
            * If the exponentitation goes beyond the number,
            * the number is divided with the base the number
            * of times the base is to multiplied to be brought
            * to a whole number.
            * @param base - base of exponent.
            * @param expected_result - The value to get.
            * @return 
            */

            double x = base;
            long long int int integer_part = x;
            double expected_result_copy = expected_result;

            for (long long int i = 0; i < integer_part; i++)
                x = x * x;
            
            if (x == expected_result)
                break;
            
            else{
                while (((expected_result_copy * 10) - expected_result_copy) != 0)
                {
                    x = x/expected_result_copy;
                    expected_result_copy = expected_result_copy * 10;
                }
            }
            return x;
        }

        double return_limit_result(double point){
            /** Explanation:
             *  Lim(variable -> point) = f(variable).
             *  In this case, variable would be equal to the point in the curve or line.
             *  Lim (variable -> point) means the curve is going to an infinitisemally small value, it might as well be the point in the curve or line.
             */
            return point;
        }

        double function_evaluation(char *expression, double point){
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

        double multivariable_integration (char** expressions , double *limits){
            
            /** Explanation of below statements:
            * Integration is analogus to addtion.
            * Differentiation is analogus to subtraction.
            * When intgeration is done, limits are the ones that are being evaluated.
            * Evaluates the functions with respect to those limits.
            * 
            * @param expressions - A matrix containing expressions.
            * @param limits - A vector containing limits. (Upper limit and then, lower limit)
            * @return result of integration.
            */

            char expression[sizeof(expressions[0])];
            double result = 0;

            for (long long int row = 0; row < sizeof(expressions); row++) //sizeof(expressions) returns the number of rows in the matrix. Learned it when programming in Java.
            {
                for (long long int column = 0; column < sizeof(expressions[0]); column++)
                    expression[column] = expressions[row][column];
                double lower_limit = function_evaluation(expression, limits[row]); // limits [(row % 2) == 0] is the lower limit.
                double upper_limit = function_evaluation(expression, limits[row+1]); // limits [(row % 2) == 1] is the upper limit.

                result = result + (upper_limit - lower_limit);
            }

            return result;
        }

        double single_variable_differentiation (double margin_of_error, double point, string expression){
            double differentiation_result = (evaluate_function(expression, point+margin_of_error) - evaluate_function(expression, margin_of_error))/ evaluate_function (expression, margin_of_error);
            return differentiation_result;
        }
};