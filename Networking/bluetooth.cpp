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
                if (index/8 == 1)
                    temporary_buffer[index] = data_buffer[index] - '0';
                else if (index/8 == 5)
                {
                    device.access_address = temporary_buffer;
                    temporary_buffer[index] = data_buffer[index] - '0';
                }

                else if ((index/8) == 262)
                {
                    //Memory cells can mean a Transistor - Capacitor cell or memory chip.
                    device.pdu = temporary_buffer;
                    temporary_buffer[index] = data_buffer[index] - '0'; //'0' - letter can give negative values
                }

                else if ((index/8) == 265)
                    device.CRC = temporary_buffer;
            }

            return device;
        }
};