namespace graph_theory{
    typedef struct map{
        // Map as a 2D matrix.
        uint8192_t length_of_map;
        uint8192_t breadth_of_map;
        long map [length_of_map][breadth_of_map];
    };
}