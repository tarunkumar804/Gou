class tcp{
  protected:
    ticks t = 0;
  public:
    char *send_tcp_message (uint32_t ipvfouraddress, uint32_t ipvsixaddress, char *tcp_header, char *data_header, char *data_frame, uint8192_t network_device_mount_point)
    {
      /** A function to send a TCP message
      * @param ipvfouraddress - IPv4 address of sender.
      * @param ipvsixaddress - IPv6 address of sender.
      * @param tcp_header - TCP header of packet.
      * @param data_header - Data header of TCP packet.
      * @param data_frame - Data frame of TCP packet.
      * @param network_device_mount_point - Mount point of network device. 
      */
     
      char *message;
      if (ipvfouraddress == 0x0)
      {
        message = [ipvsixaddress, tcp_header, data_header, data_frame];
        send_to_network_device_mount_point = message;
      }
      
      else if (ipvsixaddress == 0x0)
      {
        message = [ipvfouraddress, tcp_header, data_header, data_frame];
        send_to_network_device_mount_point = message;
      }
        return message;
    }
      
    void start_clock(uint2048_t signal_address_in_RAM)
    {
      uint8192_t tick;

      while (signal_address_in_RAM >= 0)
        tick++;  
    }
};