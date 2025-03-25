class proabibility{
    public:
        double simple_probability(double set[], double value_to_find_for){
            double count = 0, P = 0;
            for (long l = 0; l < sizeof(set); l++)
            {
                if (set[l] == value_to_find_for)
                    count++;
            }

            P = count/sizeof(set);
            return P;
        }
};