cdef extern from "metropolis_sampling.h":
    void metropolis_sampling(int num_spins, int num_cycles, double temperature,
            double *expectation_values)
