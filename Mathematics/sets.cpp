class set_theory{
    public:
        uint8129_t* return_subset(uint8219_t set[], int8192_t start_index, int8192_t end_index)
        {
            uint8129_t length_of_subset = start_index - end_index;
            uint8219_t subset[length_of_subset];

            if (length_of_subset < 0)
                 length_of_subset = (-1) * (length_of_subset);
            else if (length_of_subset >= 0)
            {
                for (int i = 0, j = start_index; i < length_of_subset, j < end_index; i++, j++)
                     subset[i] = set[i];
            }
            return subset;
        }
        
        uint8129_t* return_union (uint8219_t set1[], uint8219_t set2[], int8219_t start_index1, int8219_t end_index1, int8219_t start_index2, int8219_t end_index2)
        {
            int8219_t subset_size1 = (start_index1 - end_index1), subset_size2 = (start_index2 - end_index2);
            int i = 0, j = 0;

            if (subset_size1 < 0)
                subset_size1 = (-1) * subset_size1;
            if (subset_size2 < 0)
                subset_size2 = (-1) * subset_size2;
            uint8219_t union_set [subset_size1 + subset_size2];
            
            for (i = start_index1, j = 0; i < end_index1, j < subset_size1; i++, j++)
                  union_set[j] = set1[i];
            for (int i = start_index2, j = j; i < end_index2, j < (j+subset_size2); i++, j++)
                  union_set[j] = set2[i];
            
            return union_set;
        }
        
        uint8129_t* return_intersection (uint8219_t set [], uint8219_t values_to_intersect [])
        {
            uint8192_t intersection_set [sizeof(values_to_intersect)];
            
            for (int i = 0; i < sizeof (values_to_intersect); i++)
            {
                for (int j = 0; j < sizeof (set); j++)
                     if (values_to_intersect[i] == set[j])
                          intersection_set [i] = set[j];
            }

            return intersection_set;
        }
};