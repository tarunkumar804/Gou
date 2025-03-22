class electricity{
    public:
        uint8192_t voltage(uint8192_t radius_of_influence, uint8192_t charge)
        {
            uint8192_t voltage  = radius_of_influence * charge;
            return voltage;
        }

        uint8192_t current (uint8192_t speed_of_flow, uint8192_t voltage)
        {
            uint8192_t current = speed_of_flow * voltage;
            return current;
        }

        uint8192_t emf (uint8192_t current, uint8192_t radius_of_influence)
        {
            uint8192_t emf = current * radius_of_influence;
            return emf;
        }
};