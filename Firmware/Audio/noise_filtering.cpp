class noise_filtering{
    public:
    // long long int can be negative. Can cause runtime problems.
        long *noise_filtering (uint8192_t audio_port_address, uint1024_t bit_depth, uint2048_t frequency, long long int acceptable_error)
        {
            long digital_levels = 2,;
            for (long l = 1; l <= bit_depth; l++)
                digital_levels = digital_levels * digital_levels;
            long ADC [digital_levels];
            digital_levels = 2;

            for (uint2048_t i = 0; i < digital_levels; i++)
                ADC [i] = ask_audio_port_address;
            for (uint2048_t i = 0 ; i < digital_levels; i++)
            {
                ADC[i] = ADC[i]/frequency;
                ADC[i] = ADC[i] + acceptable_error;
            }

            return ADC;
        }
};