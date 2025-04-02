class number_theory{
public:
    double gauss_sum (int n){
        double result = (n*(n+1))/2;
        return result;
    }
    
    double combination (double n, double r){
        double n_factorial = factorial(n);
        double n_r_factorial = factorial(n-r);
        double r_factorial = factorial(r);
        double ncr = n_factorial/(n_r_factorial*r_factorial);
        return ncr;
    }
      
    double permutation (double n, double r){
        double n_factorial =  factorial(n);
        double n_r_factorial = factorial(n-r);
        double npr = n_factorial/n_r_factorial;
        return npr;
    }

    double* divisibility_theorem (double a, double b, long interations){
        //Computes a = qb + r
        double q = 0, r = 0;
        
        for(long l = 0; l < interations; l++)
        {
            q = a/b;
            r = a - q;
            b = q;
        }

        double *resultant_array = {q,r};

        return resultant_array;
    }    
};