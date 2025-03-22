class quantum_physics{
    public:
        double quantum_voltage (double particle_mass, double radius_of_influence, double charge_at_instant)
        {
            double quantum_voltage = (radius_of_influence * particle_mass)/charge_at_instant;
            return quantum_voltage;
        }

        double quantum_reverberation (double particle_mass, double quantum_frequency)
        {
            double quantum_reverberation = particle_mass * quantum_frequency;
            return quantum_reverberation;
        }

        void heisenbergs_uncertainity (double x_coordinate, double y_coordinate, double z_coordinate, double dx, double dy, double dz)
        {
            x_coordinate = x_coordinate + dx;
            y_coordinate = y_coordinate + dy;
            z_coordinate = z_coordinate + dz;
        }
};