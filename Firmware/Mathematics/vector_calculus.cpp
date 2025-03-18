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
       
       bool linear_inpedence (int512_t linear_equation_matrix**)
       {
           return true;
       }
};
