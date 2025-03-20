namespace networkdevices{
    typedef struct device{
        char *device_name; //Name of device.
        char *device_id; //Network id of device.
        uint3072_t port_number; //Attached port number.
        char *message; //Message to be sent or recieved from or to the device.
    };s
}