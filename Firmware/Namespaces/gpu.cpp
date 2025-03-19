namespace gpu{

    typedef uint8192_t luminosity; // Light intensity on an object.
    typedef uint8192_t gradients; // Image gradient.
    typedef uint8192_t shade; // Shade of an object.
    typedef uint8192_t pixel; // Pixel gradient intensity.
    typedef uint8192_t colour; // Colour value.

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
}