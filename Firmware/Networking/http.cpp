using namespace data;

class http{
  public:
    char* GET (uint8192_t data_port_address, uint8192_t network_port_address,  data_block block, uint2048_t start_address, uint8192_t end_address)
    {
      /** 
       * @param data_port_address - Port from 
       */
      char *data_stream = " ";
      block.length_of_block = end_address - start_address;
      block = new data_block();
      for (long l = 0; l < length_of_block; l++)
        block.block [l] = ask_data_port_address;
      
      return data_stream;
    }

    bool PUT (uint8192_t storage_block_address, uint8192_t network_port_address, uint8192_t number_of_storage_devices, uint8192_t sizeof_data)
    {
      send_to_storage_block_address = ask_network_port_address;
      return true;
    }
};