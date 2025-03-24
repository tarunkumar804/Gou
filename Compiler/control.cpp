class control{
    public:
        char *LDR (uint8192_t operand1, uint8192_t operand2)
        {
            char *operand1 = '0' + operand1;
            char *operand2 = '0' + operand2;
            char *instruction = {"LDR", operand1, operand2, ";"};
            return instruction;
        }
};