#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include <cmath>
#include <iostream>
#include <functional>
#include <valarray>

/// @class Distribution distributions.h "./distributions.H"
/// @brief Contains a distribution of values that can be operated on to perform Monte Carlo error propagation.
/// @tparam T the data type (`double`, `std::complex`, etc.).
/// @note As an alternative to first- or second-order error propagation for a random variable with a given mean and uncertainty, one can generate sample data reflecting those values, operate on it element-wise, and find the resulting statistics.
/// @note To implement this, this class contains a `valarray` object of the sample data along with members with statistical information.
template <typename T>
class Distribution {
    private:
        /// @brief Core members.
        std::valarray<T> _samples; ///< `valarray` containing the sample data.
        int _num_samples; ///< Size of the data.

        /// @brief Statistics of the data.
        T _mean;
        T _variance;
        T _standard_deviation;

    public:
        /// @brief Constructs a distribution from a `valarray`.
        /// @param __samples `valarray` of sample data contained within the distribution.
        Distribution(std::valarray<T> __samples) {
            _samples = __samples;
            _num_samples = __samples.size();

            /// @brief Calculates statistics of the data.
            _mean = __samples.sum() / _num_samples;
            _variance = (std::pow((_samples - _mean).apply(std::abs), 2)).sum() / _num_samples;
            _standard_deviation = std::sqrt(_variance);            
        };

        /// @brief Getters for private members.
        std::valarray<T> samples() const { return _samples; }
        std::valarray<T> data() const { return _samples; }

        int num_samples() const { return _num_samples; }
        int size() const { return _num_samples; }
        int length() const { return _num_samples; }
        int len() const { return _num_samples; }

        T mean() const { return _mean; }
        T average() const { return _mean; }
        T avg() const { return _mean; }
        
        T variance() const {return _variance; }
        T var() const {return _variance; }

        T standard_deviation() const {return _standard_deviation; }
        T std_dev() const {return _standard_deviation; }

        // TODO: cout, comparisons (compare means)
        // TODO: consider alternate implementation with Eigen package


};

#endif
