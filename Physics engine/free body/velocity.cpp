class velocity{
    public:
        void motion (uint8192_t change_in_x_direction, uint8192_t change_in_y_direction, uint8192_t change_in_z_direction, uint8192_t x_coordinate_of_object, uint8192_t y_coordinate_of_object, uint8192_t z_coordinate_of_object)
        {
            x_coordinate = x_coordinate * change_in_x_direction;
            y_coordinate = y_coordinate * change_in_y_direction;
            z_coordinate = z_coordinate * change_in_z_direction;
        }
};