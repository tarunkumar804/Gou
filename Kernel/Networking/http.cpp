class http{
  private:
    char *message = "{"; //JSON object as a string.
  public:
    char* GET (uint8192_t data_port_address, uint8192_t network_device_mount_point,  data_block block, uint2048_t start_address, uint8192_t end_address)
    {
      /** A function to implement GET request of HTTP.
      * @param data_port_address - Port to retrieve data from.
      * @param network_device_mount_point - Mount point of network device.
      * @param block - a data block.
      * @param start_address - start address of data block.
      * @param end_address - end address of data block.
      */
      char *data_stream = " ";
      block.length_of_block = end_address - start_address;
      block = new data_block();
      for (long l = 0; l < length_of_block; l++)
        block.block [l] = ask_data_port_address;
      return data_stream;
    }

    bool PUT (char *json_message, uint8192_t network_device_mount_point)
    {
      
      return true;
    }

    bool PERSIST (uint8192_t network_device_mount_point, uint8192_t storage_mount_point)
    {
      /** A function to store HTTP messages in secondary storage.
      * @param network_device_mount_point - Mount point of network device.
      * @param storage_mount_point - Mount point of storage device.
      */
      send_to_storage_mount_point = ask_network_device_mount_point;
      return true;
    }

    bool POST()
    {
      return true;
    }

    bool UPDATE ()
    {

      return true;
    }
};