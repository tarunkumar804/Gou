namespace handhelds{
    typedef struct ble_device{
        char *device_name; // Name of device.
        char *access_address; // Network id of device.
        uint3072_t port_number; // Attached port number.
        char *pdu; // Message to be sent or recieved from or to the device.
        char *CRC; // Checksum.
    };
}