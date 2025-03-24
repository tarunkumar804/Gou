class quantum_mechanics{
    public:
        bool feynman_radiation(double particle_energies[], double rate_of_loss_of_energy, int which_particle)
        {
            if (which_particle == 0)
            {
                for (;;)
                {
                    if (particle_energies[0] <= 0)
                        break;
                    particle_energies[0] = particle_energies[0] - rate_of_loss_of_energy;
                    particle_energies[1] = particle_energies[1] + rate_of_loss_of_energy;
                }
            }

            else if (which_particle == 1)
            {
                for(;;)
                {
                    if (particle_energies[1] <= 0)
                        break;
                    particle_energies[1] = particle_energies[1] - rate_of_loss_of_energy;
                    particle_energies[0] = particle_energies[0] + rate_of_loss_of_energy;
                }
            }
            return true;
        }
};