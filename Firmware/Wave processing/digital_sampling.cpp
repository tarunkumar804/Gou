class sampling{
    
    double* fourier_transform(double *wave_levels)
    {
        /** Function to perform Fast Fourier Transform.
        * @param wave_levels - voltage levels of wave.
        */

        double samples[sizeof(wave_levels)];

        for (int i = 0; i < sizeof(wave_levels); i++)
            samples[i] = wave_levels[i] - 0;
        return samples;
    }

    double ADC (double voltage_level, double bit_depth)
    {
        double digital_value = voltage_level/bit_depth;
        return digital_value;
    }
};