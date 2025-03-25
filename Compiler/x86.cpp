class x86{
    public:
        char* LDR (uint8192_t address_of_first_register, uint8192_t address_of_second_register)
        {
            char *operand1 = '0' + address_of_first_register;
            char *operand2 = '0' + address_of_second_register;
            char *instruction = {"LDR", operand1, operand2};
            return instruction;
        }

        char* ADD (uint8192_t address_of_first_register, uint8192_t address_of_second_register)
        {
            char *operand1 = '0' + address_of_first_register;
            char *operand2 = '0' + address_of_second_register;
            char *instruction = {"ADD", operand1, operand2};
            return instruction;
        }
};