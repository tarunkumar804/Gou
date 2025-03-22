class friction{
    public:
        uint8192_t Weight;

        uint8192_t friction_on_object(uint8192_t weight_on_object, uint8192_t coefficient_of_friction)
        {
            uint8192_t frictional_force = weight_on_object * coefficient_of_friction;
            return frictional_force;
        }

        uint8192_t frictional_force (uint8192_t angle_of_incidence, uint8192_t length_of_the_base)
        {
            uint8192_t tangential = angle_of_incidence/length_of_the_base;
            return tangential;
        }  
};
