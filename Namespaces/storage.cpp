namespace storage{

    typedef struct storage_unit{
          char *device_name; // Name of the storage device.
          char *device_id; // Physical ID of device.
          char *pcie_id; // PCIE ID of device.
          char *SATA_id; // SATA ID of the device.
          char *M2_id; // M.2 ID of the device.
          char *NVME_id; // NVME ID of the device.
          uint8192_t mount_point_address; // Mount pont address imof the device in RAM.
    };

    typedef struct filesystem_database{
        char *database_name; // Name of storage cluster.
        uint8192_t number_of_clusters; // Number of storage clusters.
        uint8192_t number_of_entries; // Number of storage devices.
        char cluster_names[number_of_clusters]; // Names of clusters.
        uint2048_t filesystem_matrix[number_of_clusters][number_of_entries]; // A matrix for storing the contents of filesystems.
        vector<uint8192_t> filesystem_forest; // A container for storing filesystems.
        vector<uint8192_t> data_forest; // A container for entry points for the data stored
    };
}