class bluetooth{
    public:
        ble* recieve_device_information (ble *device_block, uint64_t device_mount_point, long long int window_size)
        {
            uint64_t data_buffer [window_size];
            char temporary_buffer [2056];
            ble_device device = new ble_device();

            for (long long int index = 0; index < window_size; index++)
                data_buffer[index] = ask_device_mount_point;
            for (long long int index = 0; index < window_size; index++)
            {
                if ((index/8) == 1)
                    temporary_buffer[index] = '0' - data_buffer[index];
                
                else if (index/8 == 5)
                    device.access_address = temporary_buffer;
                else if (index/8) >= 5)
                {
                    temporary_buffer[index] = '0' - data_buffer[index];
                }
            }

            return ble_data;
        }
};