class vector_calculus {
    public:
       uint8192_t* sum_of_subspaces (uint8192_t subspaces[][], uint8192_t number_of_rows, uint8192_t number_of_columns)
       {
          /** Explanation of below statements:
          *. Sums up the elements in a column and
          *  fills up an entry in the subspace matrix.
          */
          uint8192_t subspace_sums = subspaces[number_of_columns];
          uint8192_t subspace_sum = 0;

          for (int i = 0; i < number_of_columns; i++)
          {
             for (int j = i; j < number_of_rows; j++)
                 subspace_sum = subspace_sum + subspaces[j][i];
             subspace_sums [i] = subspace_sum;
          }
          
          return subspace_sums;
       }
       
       uint8192_t direct_sum (uint8192_t subspaces_to_sum** , uint8192_t number_of_rows, uint8192_t number_of_columns)
       {
           uint8192_t direct_sum = 0;
           
           for (int i = 0; i < number_of_rows; i++)
              for (int j = 0; j < number_of_columns; j++)
                  direct_sum = direct_sum + subspaces_to_sum [i][j];
           
            return direct_sum;
       }
       
       bool is_a_linear_combination (uint8192_t vector[], uint8192_t vector1[], uint8192_t vector2[], uint8192_t vector_result[], uint8192_t lambda1, uint8192_t lambda2)
       {
           uint8192_t vector1_sum = 0, vector2_sum = 0;

           for (uint8192_t i = 0; i < sizeof(vector1); i++)
           {
               vector1[i] = lambda1 * vector1[i];
               vector1_sum = vector1_sum + vector1[i];
           }
           for (uint8192_t i = 0; i < sizeof(vector2); i++)
           {
               vector2[i] = lambda2 * vector2[i];
               vector2_sum = vector2_sum + vector2[i];
           }

           uint8192_t vector_sum = 0;

           for (uint8192_t i = 0; i < sizeof(vector); i++)
                vector_sum = vector_sum + vector[i];
            
            if (vector_sum != vector1_sum + vector2_sum)
                return false;
           return true;
       }
};
