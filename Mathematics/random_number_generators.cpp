class rng{
    public:
        uint8192_t ring_oscillator (uint8192_t number_of_not_gates, uint8192_t number_of_shift_registers, uint8192_t number_of_xor_gates, char shift_direction, int digital_signal)
        {
            uint8192_t not_gate_iteration = 0, shift_gate_iteration = 0, xor_gate_iteration = 0, random_number = digital_signal;
            
            if (shift_direction == 'L')
            {
                while (not_gate_iteration != not_gate_iteration && shift_gate_iteration != number_of_shift_registers && xor_gate_iteration != xor_gate_iteration)
                {
                    if (not_gate_iteration != not_gate_iteration)
                    {
                        random_number = ~random_number;
                        not_gate_iteration++;
                    }
                    else if (shift_gate_iteration != number_of_shift_registers)
                    {
                        random_number = random_number << 1;
                        shift_gate_iteration++;
                    }

                    else if (xor_gate_iteration != number_of_xor_gates)
                    {
                        random_number = random_number ^ 1;
                        xor_gate_iteration++;
                    }
                }
            }

            if (shift_direction == 'R')
            {
                while (not_gate_iteration != not_gate_iteration && shift_gate_iteration != number_of_shift_registers && xor_gate_iteration != xor_gate_iteration)
                {
                    if (not_gate_iteration != not_gate_iteration)
                    {
                        random_number = ~random_number;
                        not_gate_iteration++;
                    }
                    else if (shift_gate_iteration != number_of_shift_registers)
                    {
                        random_number = random_number >> 1;
                        shift_gate_iteration++;
                    }

                    else if (xor_gate_iteration != number_of_xor_gates)
                    {
                        random_number = random_number ^ 1;
                        xor_gate_iteration++;
                    }
                }
            }
        }
};