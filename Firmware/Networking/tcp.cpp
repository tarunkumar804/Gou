class tcp{
    protected:
    ticks t = 0;
    public:
      char *send_tcp_message (uint32_t ipvfouraddress, uint32_t ipvsixaddress, char *tcp_header, char *data_header, char *data_frame, uint8192_t tcp_port_address)
      {
        char *message;
        if (ipvfouraddress == 0x0)
        {
          message = [ipvsixaddress, tcp_header, data_header, data_frame];
          send_tcp_port_address = message;
        }
        else if (ipvsixaddress == 0x0)
        {
          message = [ipvfouraddress, tcp_header, data_header, data_frame];
          send_tcp_message = message;
        }

        
        return message;
      }
};