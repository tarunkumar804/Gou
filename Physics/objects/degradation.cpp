class degradation{
    public:
        uint8192_t rot(uint8192_t object_quality, uint8192_t rotting_rate, uint8192_t time_period)
        {
            for (int i = 0; i < time_period; i++)
                object_quality = object_quality * rotting_rate;
            return object_quality;
        }
};