#include <random>
#include <cmath>
#include <armadillo>

#define PERIODIC_UP(i, size) (((i) >= (size)) ? ((i) - (size)) : ((i)))
#define PERIODIC_DOWN(i, size) (((i) < 0) ? ((i) + (size)) : ((i)))

void metropolis_sampling(int num_spins, int num_cycles, double temperature,
        double *expectation_values)
{
    std::random_device rd;
    std::mt19937_64 generator(rd());

    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    double energy = 0;
    double magnetic_moment = 0;
    double diff_zero = 8;
    double diff_step = 4;

    // Create spin matrix
    arma::mat spin_matrix = arma::zeros<arma::mat>(num_spins, num_spins);
    // Fill spin matrix with ones
    spin_matrix.ones();

    // Calculate initial energy for all spin up states
    expectation_values[0] = -2*arma::sum(arma::sum(spin_matrix));
    // Calculate initial magnetic moment
    expectation_values[1] = arma::sum(arma::sum(spin_matrix));

    arma::vec energy_difference = arma::zeros<arma::mat>(5);

    for (int i = 0; i < 5; i++) {
        energy_difference(i) = exp(-(-diff_zero + i*diff_step)/temperature);
    }

    for (int cycle = 0; cycle < num_cycles; cycle++) {
        for (int i = 0; i < num_spins; i++) {
            for (int j = 0; j < num_spins; j++) {
                int ix = (int) (distribution(generator) * num_spins);
                int iy = (int) (distribution(generator) * num_spins);

                int high_ix = PERIODIC_UP(ix + 1, num_spins);
                int low_ix = PERIODIC_DOWN(ix - 1, num_spins);
                int high_iy = PERIODIC_UP(iy + 1, num_spins);
                int low_iy = PERIODIC_DOWN(iy - 1, num_spins);

                int delta_energy = 2*spin_matrix(ix, iy)
                    * (spin_matrix(ix, low_iy) + spin_matrix(ix, high_iy)
                       + spin_matrix(low_ix, iy) + spin_matrix(high_ix, iy));

                int diff_index = (delta_energy + diff_zero)/diff_step;
                if (distribution(generator) <= energy_difference(diff_index)) {
                    spin_matrix(ix, iy) *= -1.0;
                    magnetic_moment += 2*spin_matrix(ix, iy);
                    energy += delta_energy;
                }
            }
        }
        expectation_values[0] += energy;
        expectation_values[1] += magnetic_moment;
    }
}
