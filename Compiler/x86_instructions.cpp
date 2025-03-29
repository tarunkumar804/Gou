class x86_instructions{
    public:
        uint2048_t rotations (uint2048_t number, long long int number_of_iterations){
            
            /** A function to implement ROR assembly instruction
            * @param number - The number to rotate.
            * @param number_of_iterations - Number of rotations of bits.
            * @return rotated unsigned number.
            */
            uint2048_t rotated_number = 0, temporary_number = 0;
            uint8_t carry_over = 0;
        
            for (long long int l = 0; l < number_of_iterations; l++)
            {
                temporary_number = number;
                number = number >> 1; // Number gets divided by 2.
                carry_over = temporary_number - number; //Number - Temporary_number = negative number or inverted bits.
                rotated_number = number | carry_over;
            }
    
            return rotated_number;
    }
};