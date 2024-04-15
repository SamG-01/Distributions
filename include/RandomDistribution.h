#ifndef RANDOM_DISTRIBUTION_H
#define RANDOM_DISTRIBUTION_H

#include "Distribution.h"

#include <random>

/// @brief Creates source of pseudo-random numbers.
std::random_device rd;
std::default_random_engine generator;
std::mt19937 gen(rd());

/// @brief Helper function to generate `Distribution` objects using sources of random numbers.
/// @tparam T the data type.
/// @tparam DT the type of `dis`.
/// @param dis a random number distribution (see `<random>`).
/// @param _num_samples the number of samples to generate.
/// @return A `Distribution` containing the generated data.
template <typename T, typename DT>
Distribution<T> RandomDistribution(DT dis, int _num_samples) {

    std::valarray<T> _samples(_num_samples);

    for (int i = 0; i < _num_samples; i++) {
        _samples[i] = dis(gen);
    }

    return Distribution<T>(_samples);
}

/// @brief Creates a normal `Distribution` of real numbers with mean `mu` and standard deviation `sigma`.
/// @tparam T the data type. Must be `float`, `double`, or `long double`.
/// @param mu the mean of the distribution.
/// @param b the standard deviation of the distribution.
/// @param _num_samples the number of samples to generate (default 1000).
/// @return A `Distribution` containing the generated data.
template <typename T>
Distribution<T> Normal(T mu, T sigma, int _num_samples = 1000) {
    std::normal_distribution<> dis(mu, sigma);
    return RandomDistribution<T, std::normal_distribution<T>>(dis, _num_samples);
}

/// @brief Creates a uniform `Distribution` of real numbers on the interval [a, b).
/// @tparam T the data type. Must be `float`, `double`, or `long double`.
/// @param a the minimum of the distribution (inclusive).
/// @param b the maximum of the distribution (exclusive).
/// @param _num_samples the number of samples to generate (default 1000).
/// @return A `Distribution` containing the generated data.
template <typename T>
Distribution<T> Uniform(T a, T b, int _num_samples = 1000) {
    std::uniform_real_distribution<> dis(a, b);
    return RandomDistribution<T, std::uniform_real_distribution<T>>(dis, _num_samples);
}

#endif
