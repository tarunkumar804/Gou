class macroscopic_magnetism{
    public:
        uint8192_t magnetic_field_of_cuboid (uint8192_t length_of_object, uint8192_t electric_field)
        {
            uint8192_t M = (electric_field * length_of_object * length_of_object)/2;
            return M;
        }
        
        uint8192_t magnetic_field_of_sphere (uint8192_t radius_of_object, uint8192_t volumetric_height , uint8192_t electric_field)
        {
            uint8192_t M = (pi* radius_of_object * radius_of_object * volumetric_height * electric_field)/2;
            return M;
        }

        uint8192_t magnetic_field_of_pyramid (uint8192_t base_of_triangle, uint8192_t height_of_triangle, uint8192_t volumetric_height, uint8192_t electric_field)
        {
            uint8192_t M = (((base_of_triangle * height_of_triangle)/2) * volumetric_height) * electric_field;
            return M;
        }
};