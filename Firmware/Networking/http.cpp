class http{

  private:
    char message = "{";
  public:
    char* GET (uint8192_t data_port_address, uint8192_t network_port_address,  data_block block, uint2048_t start_address, uint8192_t end_address)
    {
      /** 
       * @param data_port_address - Port to retrieve data from. 
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
      send_to_storage_mount_point = ask_network_device_mount_point;
      return true;
    }

    bool UPDATE ()
    {

      return true;
    }
};