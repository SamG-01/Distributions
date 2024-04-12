#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include <valarray_math.h>

#include <iostream>
#include <functional>

/// @class distribution distributions.h "./distributions.H"
/// @brief Contains a distribution of values that can be operated on to perform Monte Carlo error propagation.
/// @tparam T the data type (`double`, `std::complex`, etc.).
/// @note As an alternative to first- or second-order error propagation for a random variable with a given mean and uncertainty, one can generate sample data reflecting those values, operate on it element-wise, and find the resulting statistics.
/// @note To implement this, this class contains a `valarray` object of the sample data along with members with statistical information.
template <typename T>
class distribution {
    private:
        /// @brief Essential data.
        std::valarray<T> _samples; ///< `valarray` of the data.
        int _num_samples; ///< Size of the data.

        /// @brief Statistics of the data.
        T _mean;
        T _variance;
        T _standard_deviation;

    public:
        /// @brief Constructs a distribution from an existing `valarray`.
        /// @param __samples `valarray` of data to convert to a distribution.
        distribution(std::valarray<T> __samples) {
            _samples = __samples;
            _num_samples = __samples.size();

            /// @brief Calculates statistics of the data.
            _mean = vaverage(__samples);
            _variance = std::pow(vaverage(pow(vabs(_samples), 2))) - pow(std::abs(_mean), 2);
            _standard_deviation = std::sqrt(_variance);
        };

        /// @brief Ready-only reference wrappers for private members.
        const std::valarray<T> samples = std::cref(_samples);
        const std::valarray<T> data = std::cref(_samples);

        const int num_samples = std::cref(_num_samples);
        const int size = std::cref(_num_samples);
        const int length = std::cref(_num_samples);
        const int len = std::cref(_num_samples);

        const T mean = std::cref(_mean);
        const T average = std::cref(_mean);
        const T avg = std::cref(_mean);
        const T nominal_value = std::cref(_mean);
        const T nom_val = std::cref(_mean);
        const T n = std::cref(_mean);

        const T variance = std::cref(_variance);
        const T var = std::cref(_variance);

        const T standard_deviation = std::cref(_standard_deviation);
        const T std_dev = std::cref(_standard_deviation);
        const T error = std::cref(_standard_deviation);
        const T s = std::cref(_standard_deviation);

        // TODO: cout, comparisons (compare means)
        // TODO: consider alternate implementation with Eigen package
};

#endif
