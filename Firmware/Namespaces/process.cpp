namespace process{
    typedef struct process_block{
        char *process_id;// A pointer to the process id stored in RAM.
        char *process_name; // Name of the process.
        char *process_data; // Data to be stored in the process for execution.
        uint8192_t number_of_services_offered; // Number of services offered that can be accessed.
        uint8192_t addresses_of_services_offered [number_of_services_offered];// A container for accessing the addressess of the services offrred.
    };
    
    typedef struct device_node{
        uint8192_t pcie_id; //Key
        uint8192_t address_in_RAM; //Value
        long long int device_type; // Numerical identifier for type of device.
    };
}