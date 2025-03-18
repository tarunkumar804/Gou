class trignometry{
    public:
        double sinusoidal (double height, double length_of_tangent)
        {
            double sinusoidal = height/length_of_tangent;
            return sinusoidal;
        }

        double cosinusoidal (double height, double length_of_tangent)
        {
            double cosinusoidal = height/length_of_tangent;
            return cosinusoidal;
        }

        double tangential (double length_of_tangent, double height)
        {
            double tangential = length_of_tangent/height;
            return tangential;
        }
};