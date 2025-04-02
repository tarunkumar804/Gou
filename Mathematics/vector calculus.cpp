class vector_calculus{
    public:

        double* subspace_sums (double **vector_matrix){

            /** A function to calculate subspace sums.
            * @authors Tarun Kumar.
            * @param vector_matrix - A matrix containing subspace elements where each row is a vector.
            * @return A vector containing subspace sums for each vector.
            */

            double subspace_sums [sizeof(set[0])], sum = 0;
            
            //Does a summation of the columns
            for (long l = 0; l < sizeof(set[0]); l++)
            {
                for (long m = 0; m < sizeof(set); m++)
                    sum = sum + set[l][m]; // Sums up the values in the column.
                subspace_sums[l] = sum;
                sum = 0;
            }

            return subspace_sums;
        }

        bool is_linear_combination(double **vector_matrix, double **reference_vectors, double *multiples)
        {
            /** A function to check for linear combination of vectors.
            * @authors Tarun Kumar.
            * @param vector_matrix - A matrix containing the vectors to check for linear combination.
            * @param reference_vectors - A matrix of reference vectors to check with.
            * @param multiplication_factors - Numbers to multiply with.
            * @return a boolean whether it is or not.
            */

            double matrix_sums[sizeof(multiples)], reference_vectors_sums[sizeof(multiples)], sum = 0;
            long long int count = 0; // To account for runtime problems.

            for (long long int row = 0; row < sizeof(vector_matrix); row++)
                for (long long int column = 0; column < sizeof(vector_matrix[0]); column++)
                    vector_matrix[row][column] = vector_matrix[row][column] * multiples[row];
            
            for (long long int row = 0; row < sizeof(vector_matrix); row++)
                for (long long int column = 0; column < sizeof(vector_matrix[0]); column++)
                    matrix_sums[row] = matrix_sums[row] + vector_matrix[row][column];
            
            for (long long int row = 0; row < sizeof(vector_matrix); row++)
                for (long long int column = 0; column < sizeof(vector_matrix[0]); column++)
                    sum = sum + reference_vectors[row][column];
                reference_vectors_sums[row] = sum;
                sum = 0;

            for (long long int row = 0; row <  sizeof(matrix_sums); row++)
                if (matrix_sums[row] == reference_vectors_sums[row])
                    count++;
            if (count != sizeof(matrix_sums))
                return false;
            return true;
        }
};