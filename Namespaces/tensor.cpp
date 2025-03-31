namespace tensor{
     typedef struct vector{
        float direction; //In degrees with respect to cardinal and non - cardinal directions.
        double magnitude;
    };
     
    typedef struct matrix {
        int row;
        int column;
        double matrix[row][column]; // Might cause runtime problems when you pass negative values to this.
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
        int length_of_set;
        int array[length_of_set];
    };
    
    typedef struct map{
        int length_of_map;
        double array[length_of_map];
    };

    typedef struct map{
        double length_of_map;
        double breadth_of_map;
        double height_of_map;
        double tensor [length_of_map][breadth_of_map][height_of_map];
    };
    
}