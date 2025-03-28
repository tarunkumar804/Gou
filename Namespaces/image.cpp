namespace image{
    typedef struct image{
        uint8192_t number_of_columns;
        uint8192_t number_of_rows;
        int8192_t red_image[number_of_rows][number_of_columns];
        int8192_t blue_image[number_of_rows][number_of_columns];
        int8192_t green_image[number_of_rows][number_of_columns];
        int8192_t yellow_image[number_of_rows][number_of_columns];
        int8192_t pixel_saturation[number_of_rows][number_of_columns];
    };

    typedef struct masked_image{
        int8192_t masked_image [15360][8640];
    };

    typedef struct segmented_image{
        int8192_t segmented_image [15360][8640];
    };

    typedef struct clustered_image{
        int8192_t clustered_image [15360][8640];
    }
}