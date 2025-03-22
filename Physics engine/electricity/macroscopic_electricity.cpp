class electricity{
    public:
        uint8192_t voltage(uint8192_t radius_of_influence, uint8192_t charge)
        {
            uint8192_t voltage  = radius_of_influence * charge;
            return voltage;
        }
};