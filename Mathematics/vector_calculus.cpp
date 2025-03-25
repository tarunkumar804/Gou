class vector_calculus{
    public:

        double** subspace_sums (double set[][]){
            double subspace_sums [sizeof(set[0])], sum = 0;
            
            //Does a summation of the columns
            for (long l = 0; l < sizeof(set[0]); l++)
            {
                for (long m = 0; m < sizeof(set); m++)
                    sum = sum + set[l][m];
                subspace_sums[l] = sum;
                sum = 0;
            }

            return subspace_sums;
        }

        bool is_linear_combination(double vector1[], double vector2[], double vector3[], double multiplication_factor1, double multiplication_factor2)
        {
            double sum1 = 0, sum2 = 0, sum3 = 0;

            for (long l = 0; l < sizeof(vector1); l++)
            {
                vector2[l] = vector2[l] * multiplication_factor1;
                sum2 = sum2 + vector2[l];
            }

            for (long l = 0; l < sizeof(vector2); l++)
            {
                vector3[l] = vector3[l] * multiplication_factor2;
                sum3 = sum3 + vector3[l];
            }

            for (long l = 0; l < sizeof(vector1); l++)
                sum1 = sum1 + vector1[l];
            if (sum1 == (sum2 + sum3))
                return false;
            return true;
        }
};