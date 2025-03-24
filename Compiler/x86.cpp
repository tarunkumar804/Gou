class x86{
    public:
    char *ADD (uint8192_t operand1, uint8192_t operand2)
    {
        char *operand1 = '0' + operand1;
        char *operand2 = '0' + operand2;
        char *instruction = {"ADD", operand1, operand2, ";"};
        return instruction;
    }

    char *MUL (uint8192_t operand1, uint8192_t operand2)
    {
        char *operand1 = '0' + operand1;
        char *operand2 = '0' + operand2;
        char *instruction = {"MUL", operand1, operand2, ";"};
        return instruction;
    }

    char *UMULL (uint8192_t operand1, uint8192_t operand2)
    {
        char *operand1 = '0' + operand1;
        char *operand2 = '0' + operand2;
        char *instruction = {"UMULL", operand1, operand2, ";"};
        return instruction;
    }

    char *SUB (uint8192_t operand1, uint8192_t operand2)
    {
        char *operand1 = '0' + operand1;
        char *operand2 = '0' + operand2;
        char *instruction = {"SUB", operand1, operand2, ";"};
        return instruction;
    }

    char *DIV (uint8192_t operand1, uint8192_t operand2)
    {
        char *operand1 = '0' + operand1;
        char *operand2 = '0' + operand2;
        char *instruction = {"DIV", operand1, operand2};
        return instruction;
    }

    char* STR (uint8192_t number)
    {
        char *operand1 = '0' + number;
        char *instruction = {"STR",operand1};
        return STR;
    }
};