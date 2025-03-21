class wave{
    public:
        long* generate_wave (double starting_degree, long bit_depth)
        {
            /** A function to generate a wave in digital values.
            *  @param bit_depth - number of steps.
            *  @param starting_degree - starting wave degree.
            *. @return generated wave in digital values.
            */

            long maximum_resolution = 2;// 2^0
           
            for (int i = 2; i <= bit_depth; i++)
                maximum_resolution = maximum_resolution * maximum_resolution; //Exponentiating until the maximum resolution.
            long wave_in_digital_levels [maximum_resolution * 4], temporary_number =  bit_depth; // 4 times for positive half (x2) (above 0) and negative half (x2) (below 0).
            wave_in_digital_levels [0] = 1; //2^0.

            for (int i = 1; i <= maximum_resolution; i++) //Positive half
            {
                if (i == 1)
                    wave_in_digital_levels [i] = bit_depth;
                else if (i > 1)
                {
                    temporary_number = temporary_number * temporary_number; //Ascending
                    wave_in_digital_levels [i] = temporary_number;
                }
            }
            
            for (int i = maximum_resolution; i >= 0 ; i--) //Positive half
            {
                wave_in_digital_levels [i] = temporary_number/2;//Descending
                temporary_number = temporary_number/2;
            }
 
            for (int i = 0; i < maximum_resolution; i++)
                wave_in_digital_levels [i+maximum_resolution] = -(wave_in_digital_levels[i]); //Negative half
            return wave_in_digital_levels;
        }
};