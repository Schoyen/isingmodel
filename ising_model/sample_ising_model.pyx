import numpy as np
cimport numpy as np

def compute_expectation_values(int num_spins, int num_cycles,
        np.ndarray[double, ndim=1] temperatures):

    # We use expectation_values = [energy, magnetic_moment]
    cdef np.ndarray[double, ndim=1, mode="c"] expectation_values
    cdef double temperature, norm
    cdef dict expectation_value_dict

    # Setup initial expectation values
    expectation_values = np.zeros(2)

    expectation_value_dict = {
        'temperature': [],
        'energy': [],
        'magnetic_moment': []
    }

    norm = 1.0/float(num_cycles*num_spins**2)

    for temperature in temperatures:
        metropolis_sampling(num_spins, num_cycles, temperature,
            &expectation_values[0])

        expectation_values *= norm
        expectation_value_dict['temperature'].append(temperature)
        expectation_value_dict['energy'].append(expectation_values[0])
        expectation_value_dict['magnetic_moment'].append(expectation_values[1])

    return expectation_value_dict
