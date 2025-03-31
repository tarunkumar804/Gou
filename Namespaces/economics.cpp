namespace economics{
    
    typedef struct cash flow{
       long long int number_of_cash_flows;
        double cash_flows[number_of_cash_flows];
    };

    typedef struct single_payment_future_amount{
        double principal;
        double interest_rate;
        double payment_period;
        double future_amount;
    };

    typedef struct uniform_annual_payments_future_amount{
        double principal;
        double number_of_cash_flows;
        double cash_flows[number_of_cash_flows];
        double interest_rate;
        double payment_period;
        double future_amount;
    };

    typedef struct annual_payments_future_amount{
        double principal;
        double number_of_cash_flows;
        double cash_flows[number_of_cash_flows];
        double interest_rate;
        double payment_period;
        double future_amount;
    };

    typedef struct arithmetic_series{
        double arthimetic_factor;
        double number_of_cash_flows;
        double cash_flows[number_of_cash_flows];
    };

    typedef struct geometric_series{
        double geometric_factor;
        double number_of_cash_flows;
        double cash_flows[number_of_cash_flows];
    };

    typedef struct geometric_series{
        double geometric_factor;
    };

    typedef struct rate_of_return{
        double rate_of_return_1;
        double rate_of_return_2;
        double present_worth_1;
        double present_worth_2;
    };

    typedef struct alternative{ //Economic alternative
        double number_of_costs;
        double number_of_types_of_costs;
        double costs_matrix[number_of_types_of_costs][number_of_costs];
    };
}