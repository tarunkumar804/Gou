#include <vector>
#include <random>
#include <algorithm>

class quantum_mechanics {
public:
    // Constructor to initialize the random number generator
    quantum_mechanics() : generator(std::random_device{}()) {}

    /**
     * Simulates energy radiation from a source particle to others in discrete quanta over time steps.
     * @param particle_energies Vector of particle energies, modified in place
     * @param rate_of_loss_of_energy Rate of energy loss per unit time (energy/time)
     * @param source_particle Index of the particle losing energy
     * @param delta_energy Size of each energy quantum transferred
     * @param time_step Duration of each simulation time step
     * @param max_steps Maximum number of simulation steps
     * @return true if simulation completes successfully, false if inputs are invalid
     */
    bool feynman_radiation(std::vector<double>& particle_energies,
                          double rate_of_loss_of_energy,
                          int source_particle,
                          double delta_energy,
                          double time_step,
                          int max_steps) {
        // Input validation
        if (particle_energies.size() < 2 ||
            source_particle < 0 ||
            source_particle >= particle_energies.size() ||
            rate_of_loss_of_energy <= 0 ||
            delta_energy <= 0 ||
            time_step <= 0 ||
            max_steps <= 0) {
            return false;
        }

        // Poisson parameter: expected number of transfers per time step
        double lambda = (rate_of_loss_of_energy / delta_energy) * time_step;
        std::poisson_distribution<int> distribution(lambda);

        // Simulate for up to max_steps
        for (int step = 0; step < max_steps; ++step) {
            // Stop if insufficient energy for even one quantum
            if (particle_energies[source_particle] < delta_energy) {
                break;
            }

            // Number of quanta to transfer this step
            int k = distribution(generator);
            double max_k = std::floor(particle_energies[source_particle] / delta_energy);
            k = std::min(k, static_cast<int>(max_k));
            double energy_to_transfer = k * delta_energy;

            // Update energies
            particle_energies[source_particle] -= energy_to_transfer;
            double share = energy_to_transfer / (particle_energies.size() - 1);
            for (size_t i = 0; i < particle_energies.size(); ++i) {
                if (i != source_particle) {
                    particle_energies[i] += share;
                }
            }
        }
        return true;
    }

private:
    std::mt19937 generator; // Mersenne Twister random number generator
};
