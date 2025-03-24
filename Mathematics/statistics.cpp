class statistics{
    double mean (double set[]){
        double mean = 0, sum = 0;
        for (int i = 0; i < sizeof(set); i++)
            sum = sum + set[i];
        mean = sum/sizeof(set);

        return mean;
    }

    double standard_deviation(double set[]){
        double mean = 0, sum = 0, standard_deviation = 0, intermediate_array[sizeof(set)], temporary_copy = 0;

        for (int i = 0; i < sizeof(set); i++)
            sum = sum + set[i];
        mean = sum/sizeof(set);

        sum = 0;

        for (int i = 0; i < sizeof(set); i++)
        {
            intermediate_array[i] = intermediate_array[i] - mean;
            intermediate_array[i] = (intermediate_array[i] * intermediate_array[i]);
            sum = sum + intermediate_array[i];
        }

        standard_deviation = standard_deviation/sizeof(intermediate_array);
        temporary_copy = standard_deviation;
        while (((standard_deviation * 10) - standard_deviation) != 0)
            //Calculates square root of 2
            temporary_copy = temporary_copy/2;
        standard_deviation = temporary_copy;
        return standard_deviation;
    }
};