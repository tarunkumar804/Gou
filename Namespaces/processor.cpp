namespace processor{
   typedef struct processor_information{
       char *processor_name;
       uint8192_t processor_pcie_address;
       uint8192_t number_of_computation_processors;
       uint8192_t number_of_tensor_processors;
       uint8192_t addresses_of_computation_processors [number_of_computation_processors];
       uint8192_t addresses_of_tensor_processors [number_of_tensor_processors];
       double clock_frequency;
       uint8192_t number_of_L1_caches;
       uint8192_t number_of_L2_caches;
       uint8192_t number_of_L3_caches;
       uint8192_t number_of_L4_caches;
       uint8192_t addresses_of_L1_caches [number_of_L1_caches];
       uint8192_t addresses_of_L2_caches [number_of_L2_caches];
       uint8192_t addresses_of_L3_caches [number_of_L3_caches];
       uint8192_t addresses_of_L4_caches [number_of_L4_caches];
       uint8192_t UTC_clock;
       uint8192_t timezone_difference;
       char *timezone;
   };

   typedef struct cache_block{ // A block in RAM that can be used to store data in local caches.
      char *address_of_entry_point; //Mount point of cache.
      char *data;
   };
}