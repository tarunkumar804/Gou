namespace gpu{

    typedef struct display_depth{
        long long int bit_depth;
        char image_to_send[bit_depth][bit_depth];
    };

    typedef struct gpu_information{
        uint1024_t gpu_start_address_in_RAM;
        uint1024_t gpu_end_address_in_RAM;
        long long int number_of_gpus;
        char gpu_names[number_of_gpus];
        long long int pcie_ids[number_of_gpus]; //Container for PCIE ids
        uint1024_t pcie_address[number_of_gpus]; //Container for PCIE addresses in RAM.
    };

    typedef struct gpu_cluster{
        uint8192_t number_of_gpus;
        uint8192_t mount_points_of_gpus[number_of_gpus];
    };
}