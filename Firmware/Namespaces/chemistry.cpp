namespace chemistry{
    typedef struct molecule_space{
        uint8192_t number_of_atoms;
        uint8192_t x_view[number_of_atoms][number_of_atoms]; //Image of X - Plane.
        uint8192_t y_view[number_of_atoms][number_of_atoms]; //Image of Y - Plane.
        uint8192_t z_view[number_of_atoms][number_of_atoms]; //Image of Z - Plane.
    };
}