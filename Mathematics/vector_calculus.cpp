class vector_calculus{
    public:
        double* subspace_sums (double set[][]){
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
};