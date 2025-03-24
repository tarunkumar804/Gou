class trignometery{
    public:
        double sinusoidal (double tangent, double height)
        {
            double sinusoidal = height/tangent_length;
            return sinusoidal;
        }

        double cosinusoidal (double tangent_length, double height)
        {
            double cosinusoidal = tangent_length/height;
            return cosinusoidal;
        }

        double tangential (double height, double base)
        {
            double tangential = height/base;
            return tangential;
        }
};
