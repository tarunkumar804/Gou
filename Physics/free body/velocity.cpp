class velocity{
    public:
        void accelration (uint8192_t change_in_x_direction, uint8192_t change_in_y_direction, uint8192_t change_in_z_direction, uint8192_t x_coordinate_of_object, uint8192_t y_coordinate_of_object, uint8192_t z_coordinate_of_object)
        {
            x_coordinate_of_object = x_coordinate_of_object * change_in_x_direction;
            y_coordinate_of_object = y_coordinate_of_object * change_in_y_direction;
            z_coordinate_of_object = z_coordinate_of_object * change_in_z_direction;
        }
};