unamespace tensor{
     typedef struct vector{
         float8192_t direction; //In degrees with respect to cardinal and non - cardinal directions.
         double8192_t magnitude;
     };
     
     typedef struct matrix {
          int8192_t row;
          int8192_t column;
          double8192_t matrix[row][column]; // Might cause runtime problems when you pass negative values to this.
     };
     
     typedef struct subspace{
        uint8192_t subspace_size;
        uint8192_t subspace[array_size];
    };

    typedef struct span{
        uint8192_t span_size;
        uint8192_t span[span_size];
    };

    typedef struct set{
        int8192_t length_of_set;
        int8192_t array[length_of_set];
    };
    
    typedef struct linear_map{
        int8192_t length_of_map;
        double8192_t array[length_of_map];
    };

    typedef struct map{
        double8192_t length_of_map;
        double8192_t breadth_of_map;
        double8192_t height_of_map;
        double8192_t tensor [length_of_map][breadth_of_map][height_of_map];
    }
    
}