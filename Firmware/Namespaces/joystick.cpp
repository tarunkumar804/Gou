namespace joystick{
    typedef struct analog_pads{
           uint8192_t radius_of_analog_pads;
           uint8192_t padding;
           uint8192_t analog_senstivity [radius_of_analog_pads + padding][radius_of_analog_pads + padding];
    };
 
    typedef struct buttons{
          double8192_t button_matrix [5192][5192];
          double8192_t trigger_matrix [16][16];
    };
    
    typedef struct touchpad{
         uint8192_t tft_voltage;
         uint8129_t padding;
         double8192_t sense_matrix [tft_voltage + padding][tft_voltage + padding];
    };

    typedef struct circular_array{ //A way of mapping voltages of analog sticks of joystick.
         uint8192_t radius_of_circle;
         uint8192_t padding;
         double8192_t voltage_matrix [radius_of_circle + padding][radius_of_circle + padding];
    };
    
    typedef double8192_t power;
}