class http{
  public:
    char* GET (uint8192_t data_port_address, uint8192_t network_port_address,  data_block block, uint2048_t start_address, uint8192_t end_address)
    {
      /** 
       * @param data_port_address - 
       */
      char *data_stream = " ";
      block.length_of_block = end_address - start_address;
      block = new data_block();
      for (long l = 0; l < length_of_block; l++)
        block.block [l] = ask_data_port_address;
      
      return data_stream;
    }
};