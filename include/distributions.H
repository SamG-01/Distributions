#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include <valarray_math.h>

#include <iostream>

/// @class distribution distributions.h "distributions.H"
/// @brief Contains a distribution of values that can be operated on to perform Monte Carlo error propagation.
/// @tparam T the data type.
/// @note As an alternative to first- or second-order error propagation for a random variable with a given mean and uncertainty, one can generate sample data reflecting those values, operate on it element-wise, and find the resulting statistics.
/// @note To implement this, this class contains a `valarray` object of the sample data along with members with statistical information.
template <typename T>
class distribution {
    private:
        /// @brief Essential data.
        std::valarray<T> _samples; ///< Valarray of the data.
        int _num_samples; ///< Size of the data.

        /// @brief Statistical information for the data.
        T _mean;
        T _variance;
        T _standard_deviation;

    public:
        /// @brief Constructs a distribution from an existing valarray.
        /// @param __samples Valarray of data to convert to a distribution.
        distribution(std::valarray<T> __samples) {
            _samples = __samples;
            _num_samples = __samples.size();

            /// @brief Calculates the statistical information.
            _mean = vaverage(__samples);
            _variance = std::pow(vaverage(pow(vabs(_samples), 2))) - pow(std::abs(_mean), 2);
            _standard_deviation = std::sqrt(_variance);
        };

        /// @brief Ready-only getters for private members.
        const auto& samples = _samples;
        const auto& data = _samples;

        const auto& num_samples = _num_samples;
        const auto& size = _num_samples;
        const auto& length = _num_samples;
        const auto& len = _num_samples;

        const auto& mean = _mean;
        const auto& average = _mean;
        const auto& avg = _mean;
        const auto& nominal_value = _mean;
        const auto& nom_val = _mean;
        const auto& n = _mean;

        const auto& variance = _variance;
        const auto& var = _variance;

        const auto& standard_deviation = _standard_deviation;
        const auto& std_dev = _standard_deviation;
        const auto& error = _standard_deviation;
        const auto& s = _standard_deviation;

        // TODO: cout, comparisons (compare means)
};

#endif
