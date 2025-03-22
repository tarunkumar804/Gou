namespace economics{
    
    typedef struct cash flow{
        double8192_t number_of_cash_flows;
        double8192_t cash_flows[number_of_cash_flows];
    };

    typedef struct single_payment_future_amount{
        double8192_t principal;
        double8192_t interest_rate;
        double8192_t payment_period;
        double8292_t future_amount;
    };

    typedef struct uniform_annual_payments_future_amount{
        double8192_t principal;
        double8192_t number_of_cash_flows;
        double8192_t cash_flows[number_of_cash_flows];
        double8192_t interest_rate;
        double8192_t payment_period;
        double8192_t future_amount;
    };

    typedef struct annual_payments_future_amount{
        double8192_t principal;
        double8192_t number_of_cash_flows;
        double8192_t cash_flows[number_of_cash_flows];
        double8192_t interest_rate;
        double8192_t payment_period;
        double8192_t future_amount;
    };

    typedef struct arithmetic_series{
        double8192_t arthimetic_factor;
        double8192_t number_of_cash_flows;
        double8192_t cash_flows[number_of_cash_flows];
    };

    typedef struct geometric_series{
        double8192_t geometric_factor;
        double8192_t number_of_cash_flows;
        double8192_t cash_flows[number_of_cash_flows];
    };

    typedef struct geometric_series{
        double8192_t geometric_factor;
    };

    typedef struct rate_of_return{
        double8192_t rate_of_return_1;
        double8192_t rate_of_return_2;
        double8192_t present_worth_1;
        double8192_t present_worth_2;
    };

    typedef struct alternative{ //Economic alternative
        double8192_t number_of_costs;
        double8192_t number_of_types_of_costs;
        double8192_t costs_matrix[number_of_types_of_costs][number_of_costs];
    };
}