namespace animation{
    typedef struct film{
         uint8192_t length_of_film;
         uint8192_t breadth_of_film;
         uint8192_t film [length_of_film][breadth_of_film];
    };
    
    typedef struct film_reel{
         uint8192_t number_of_films;
         uint8192_t length_of_film;
         uint8192_t breadth_of_film;
         uint8192_t film [length_of_film][breadth_of_film];
         film reel [number_of_films];
    };

    typedef struct frame{
         uint8192_t length_of_frame;
         uint8192_t width_of_frame;
         uint8192_t frame [length_of_frame][width_of_frame];
         uint8192_t colour [length_of_frame][width_of_frame];
         uint8192_t luminiosity [length_of_frame][width_of_frame];
         uint8192_t colour_gradient [length_of_frame][width_of_frame];
    };
    
    typedef struct video {
         uint8192_t fps;
         frame frames [fps];
    };
}