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

        char* STR (uint8192_t address_of_data_register)
        {
            char *STR = {"STR",number};
            return STR;
        }

        char *LDR (uint8192_t first_register_address, uint8192_t second_regsiter_address)
        {
            char *operand1 = '0' + operand1;
            char *operand2 = '0' + operand2;
            char *instruction = {"LDR", operand1, operand2, ";"};
            return instruction;
        }

        char *MUL (uint8192_t first_register_address, uint8192_t second_register_address)
        {
            char *operand1 = '0' + operand1;
            char *operand2 = '0' + operand2;
            char *instruction = {"MUL", operand1, operand2, ";"};
            return instruction;
        }

        char *UMULL (uint8192_t first_register_address, uint8192_t second_register_address)
        {
            char *operand1 = '0' + operand1;
            char *operand2 = '0' + operand2;
            char *instruction = {"UMULL", operand1, operand2, ";"};
            return instruction;
        }

        char *SUB (uint8192_t first_register_address, uint8192_t second_register_address)
        {
            char *operand1 = '0' + operand1;
            char *operand2 = '0' + operand2;
            char *instruction = {"SUB", operand1, operand2, ";"};
            return instruction;
        }

        char *DIV (uint8192_t first_register_address, uint8192_t second_register_address)
        {
            char *operand1 = '0' + operand1;
            char *operand2 = '0' + operand2;
            char *instruction = {"DIV", operand1, operand2};
            return instruction;
        }
};