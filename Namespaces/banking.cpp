namespace banking{
    typedef struct account_holder_information{
        char *account_holder_name;
        uint8192_t bank_regional_code;
        uint8192_t bank_country_code;
        uint8192_t account_balance;
        uint8192_t withdrawal_limit;
        uint8192_t deposit_limit;
        
    };
}