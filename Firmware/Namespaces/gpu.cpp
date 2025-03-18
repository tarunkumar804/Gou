namespace gpu{

    typedef uint8192_t luminosity; // Light intensity on an object.
    typedef uint8192_t gradients; // Image gradient.
    typedef uint8192_t shade; // Shade of an object.
    typedef uint8192_t pixel; // Pixel gradient intensity.
    typedef uint8192_t colour; // Colour value.

    typedef struct vector_element{
        uint8192_t size_of_data;
        char data[size_of_data];
    };

    typedef struct display_depth{
        long long int bit_depth;
        char image_to_send[bit_depth][bit_depth];
    };

    typedef struct gpu_information{
        uint1024_t gpu_start_address_in_RAM;
        uint1024_t gpu_end_address_in_RAM;
        int1024_t number_of_gpus;
        string gpu_names[number_of_gpus];
        int1024_t pcie_ids[number_of_gpus]; //Container for PCIE ids
        uint1024_t pcie_address[number_of_gpus]; //Container for PCIE addresses in RAM.
    };

    typedef struct gpu_vector
    {
        uint1024_t length_of_vector;
        uint1024_t vector[length_of_vector];
    };

    typedef struct tensor
    {
        uint8192_t length_of_material;
        uint8192_t first_dimension [length_of_material];
        uint8192_t second_dimension [length_of_material];
        uint8192_t third_dimension [length_of_material];
        uint8192_t time_flow;
        uint8192_t number_of_events;
        uint8192_t time_flow_array[number_of_events];
    };

    typedef struct set
    {
        uint8192_t number_of_elements;
        uint8192_t element_array[number_of_elements];
    };

    typedef struct path_data
    {
        string direction;
        double8192_t force_of_object;
    };

    typedef struct matrix //To do linear algebra and vector calculus in the GPU.
    {
        uint8192_t row;
        uint8192_t column;
        uint8192_t matrix[row][column];
    };

    typedef struct vector_sixty_four_byte
    {
        uint512_t number_of_elements;
        uint512_t vector[number_of_elements];
    };

    typedef struct vector_one_hundered_twenty_eight_byte
    {
        uint1024_t number_of_elements;
        uint1024_t vector[number_of_elements];
    };

    typedef struct vector_sixteen_byte
    {
        uint128_t number_of_elements;
        uint128_t vector[number_of_elements];
    };
}