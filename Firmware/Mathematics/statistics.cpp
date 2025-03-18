class statistics{
    public:
       double8192_t mean (double8192_t set[])
       {
          double8192_t mean = 0, sum = 0;
          for (long long int i = 0; i < sizeof(set); i++)
               sum = sum + set [i];
          mean = sum/sizeof(set);
          return mean;
       }
       
       double8192_t standard_deviation (double8192_t set[])
       {
           double8192_t mean = mean(set), sum = 0, standard_deviation = 0;
           
           for (long long int i = 0; i < sizeof(set); i++)
               sum = sum + ((set[i] - mean) * (set[i] - mean));
           double8192_t intermediate_result = sum/sizeof(set);
           
            
           return standard_deviation;
       }
};