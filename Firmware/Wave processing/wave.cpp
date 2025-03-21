class wave{
    public:
        long* generate_wave (double starting_degree, long bit_depth)
        {
            /** A function to generate a wave in digital values.
            *  @param bit_depth - number of steps.
            *  @param starting_degree - starting wave degree.
            *. @return generated wave in digital values.
            */

            long maximum_resolution = 2;
           
            for (int i = 2; i <= bit_depth; i++)
                maximum_resolution = maximum_resolution * maximum_resolution;
            long wave_in_digital_levels [maximum_resolution * 4], temporary_number =  bit_depth;
            wave_in_digital_levels [0] = 1;

            for (int i = 1; i <= maximum_resolution; i++)
            {
                if (i == 1)
                    wave_in_digital_levels [i] = bit_depth;
                else if (i > 1)
                {
                    temporary_number = temporary_number * temporary_number;
                    wave_in_digital_levels [i] = temporary_number;
                }
            }
            
            for (int i = maximum_resolution; i >= 0 ; i--)
            {
                wave_in_digital_levels [i] = temporary_number/2;
                temporary_number = temporary_number/2;
            }
 
            for (int i = 0; i < maximum_resolution; i++)
                wave_in_digital_levels [i+maximum_resolution] = -(wave_in_digital_levels[i]);
            return wave_in_digital_levels;
        }
};