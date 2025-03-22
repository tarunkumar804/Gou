class particle_physics{
    public:
        double cyclotron_accelration(double radius, double dv, long number_of_revolutions,double thickness)
        {
            /** A function to simulate accelaration in a cyclometer.
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

        double particle_collison (double thickness, double decrease_in_thickness)
        {
            //Decrease in thickness per increase in speed.
            double collison_speed = thickness/decrease_in_thickness;
            double collateral = 0, current_speed = 0;
            
            while (current_speed != collison_speed)
            {
                if (current_speed < collison_speed)
                {
                    current_speed = current_speed ++;
                    collateral++;
                }

                else if (current_speed > collison_speed)
                {
                    current_speed = current_speed / collison_speed;
                    collateral = collateral/decrease_in_thickness;
                }
            }

            return collateral;
        }
};