namespace peripherals {
    typedef struct usb {
         uint8192_t number_of_usb_devices;
         uint8192_t usb_device_addresses [number_of_usb_devices]; //Mount points of USB devices.
    };
    
   typedef struct mouse{
        uint8192_t area; // Area of the touchpad.
        uint8192_t volumetric_area; // 3D area around the pointing device.
        uint8192_t z_matrix_three_dimensional; // Circular heightwise-region around the pointing device.
        uint8192_t y_matrix_three_dimensional; // Circular vertical-region around the pointing device.
        uint8192_t x_matrix_three_dimensional; // Circular horizontal-region around the pointing device.
        uint8192_t x_matrix; // Length of the mouse mat.
        uint8192_t y_matrix; // Breadth of the mouse mat.
        uint8192_t z_matrix; // Porous height of the mouse mat.
   };
}