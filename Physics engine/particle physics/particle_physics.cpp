class particle_physics{
    public:
        double cyclotron_accelration(double radius, double dv, long number_of_revolutions,double thickness)
        {
            /** 
            * @param radius - radius of the accelrometer from a pivot element.
            * @param dv - infinitismally small value of velocity.
            * @param number_of_revolutions - number of revolutions in the accelrometer.
            * @param thickness - thickness of the accelrometer.
            */

            double area = pi * radius * radius;
            area = area - (area * (3/4)); //To get the doughnut shape of the accelrator.
            area = area * thickness; //To get the cyclotron with thickness.

            for (long i = 0; i < number_of_revolutions; i++)
            {
                // To revolve the particle in the accelrator

                for (long l =  0; l < area; l++)
                    dv = dv + dv;
            }

            return dv;
        }
};