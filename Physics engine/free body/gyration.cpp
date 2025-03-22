class gyration{
    public:
        bool rotation_of_object(double8192_t x_coordinate, double8192_t y_coordinate, double8192_t z_coordinate, bool rotate_from_base, bool rotate_from_height, bool rotate_from_tangential)
        {
            trignometry t = new trignometry();

            if (rotate_from_base == true)
            {
                double cosinusoidal = t.cosinusoidal(y_coordinate, x_coordinate);
                x_coordinate = x_coordinate * cosinusoidal;
                y_coordinate = y_coordinate * cosinusoidal;
                z_coordinate = z_coordinate * cosinusoidal;
            }

            else if (rotate_from_height == true)
            {
                double sinusoidal = t.sinusoidal (x_coordinate, y_coordinate);
                x_coordinate = x_coordinate * sinusoidal;
                y_coordinate = y_coordinate * sinusoidal;
                z_coordinate = z_coordinate * sinusoidal;
            }

            else if (rotate_from_tangential == true)
            {
                double tangential = t.tangential (x_coordinate, y_coordinate);
                x_coordinate = x_coordinate * tangential;
                y_coordinate = y_coordinate * tangential;
                z_coordinate = z_coordinate * tangential;
            }

            return true;
        }
};