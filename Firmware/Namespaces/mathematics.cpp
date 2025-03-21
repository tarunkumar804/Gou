namespace mathematical{
     const double pi = 22/7;// A variable to calculate the irrational number Pi according to the amount of precision that can be adjustable according to the bit length of the processor.
     const int positive_inf = (1/0);
     const int negative_inf = -(1/0);

     typedef struct set{
          uint8192_t length_of_array;
          uint8192_t array [length_of_array];
     };

     typedef struct matrix{
          uint8192_t number_of_rows;
          uint8192_t number_of_columns;
          uint8192_t matrix[number_of_rows][number_of_columns];
     };

     typedef struct tensor{
          uint8192_t length_of_material;
          uint8192_t first_dimension [length_of_material];
          uint8192_t second_dimension [length_of_material];
          uint8192_t third_dimension [length_of_material];
          uint8192_t time_flow;
          uint8192_t number_of_events;
          uint8192_t time_flow_array[number_of_events];
     };
  
     typedef struct path_data{
          string direction;
          double8192_t force_of_object;
     };
  
     typedef struct matrix{
          uint8192_t row;
          uint8192_t column;
          uint8192_t matrix[row][column];
     };
  
     typedef struct vector_sixty_four_byte{
          uint512_t number_of_elements;
          uint512_t vector[number_of_elements];
     };
  
      typedef struct vector_one_hundered_twenty_eight_byte{
          uint1024_t number_of_elements;
          uint1024_t vector[number_of_elements];
     };
  
     typedef struct vector_sixteen_byte{
          uint128_t number_of_elements;
          uint128_t vector[number_of_elements];
     };
     
     typedef struct gpu_vector{
          uint1024_t length_of_vector;
          uint1024_t vector[length_of_vector];
     };
  
     typedef struct path_data{
          string direction;
          double8192_t force_of_object;
     };
  
     typedef struct matrix{
          uint8192_t row;
          uint8192_t column;
          uint8192_t matrix[row][column];
     };
  
     typedef struct vector_sixty_four_byte{
          uint512_t number_of_elements;
          uint512_t vector[number_of_elements];
     };
  
     typedef struct vector_one_hundered_twenty_eight_byte{
          uint1024_t number_of_elements;
          uint1024_t vector[number_of_elements];
     };
  
     typedef struct vector_sixteen_byte{
          uint128_t number_of_elements;
          uint128_t vector[number_of_elements];
     };
}