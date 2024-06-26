#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include <cmath>
#include <iostream>
#include <functional>
#include <valarray>

/// @class Distribution distributions.h "./distributions.H"
/// @brief Contains a distribution of values that can be operated on to perform Monte Carlo error propagation.
/// @tparam T the data type (`double`, `float`, etc.).
/// @brief As an alternative to first- or second-order error propagation for a random variable with a given mean and uncertainty, one can generate sample data reflecting those values, operate on it element-wise, and find the resulting statistics.
/// @brief To implement this, this class contains a `valarray` object of the sample data along with members with statistical information.
template <typename T>
class Distribution {
    private:
        // Core members.
        std::valarray<T> _samples; ///< `valarray` containing the sample data.
        int _num_samples; ///< Size of the data.

        // Statistics of the data.
        T _mean;
        T _variance;
        T _standard_deviation;

    public:
        // Constructs a distribution from a `valarray`.
        /// @param __samples `valarray` of sample data contained within the distribution.
        Distribution(std::valarray<T> __samples) {
            _samples = __samples;
            _num_samples = __samples.size();

            // Calculates statistics of the data.
            _mean = __samples.sum() / _num_samples;
            _variance = (std::pow((_samples - _mean).apply(std::abs), 2)).sum() / _num_samples;
            _standard_deviation = std::sqrt(_variance);            
        };

        // Getters for private members.
        std::valarray<T> samples() const { return _samples; }
        std::valarray<T> data() const { return _samples; }

        /// @brief Number of samples.
        int num_samples() const { return _num_samples; }
        int size() const { return _num_samples; }
        int length() const { return _num_samples; }
        int len() const { return _num_samples; }

        /// @brief Average of the samples.
        T mean() const { return _mean; }
        T average() const { return _mean; }
        T avg() const { return _mean; }
        
        /// @brief Variance of the samples.
        T variance() const {return _variance; }
        T var() const {return _variance; }

        /// @brief Standard deviation of the samples.
        T standard_deviation() const {return _standard_deviation; }
        T std_dev() const {return _standard_deviation; }

        /// @brief Provides read-only access to the (i+1)-th sample in the distribution.
        /// @param i the index.
        /// @return _samples[i].
        const T& operator[](int i) const {
            return _samples[i];
        }

        // Methods

        /// @brief Applies a function to `samples` element-wise.
        /// @param func the function to be applied.
        /// @return The resulting distribution.
        Distribution<T> apply(T func(T)) {
            return Distribution<T>(_samples.apply(func));
        }

        /// @brief Computes the covariance of two `Distribution`s.
        /// @param Dist2 the second distribution.
        /// @return The covariance of `this` and `Dist2`.
        T covariance(const Distribution<T> Dist2) {
            Distribution<T> Dist3 = Distribution<T>((_samples - _mean) * (Dist2.samples() - Dist2.mean()));
            return Dist3.mean();
        }

        // `Distribution`-`Distribution` operations

        /// @brief Add `Distribution`s by adding their samples element-wise.
        /// @param Dist2 second summand.
        /// @return The resulting distribution.
        Distribution<T> operator+ (const Distribution<T> Dist2) {
            return Distribution<T>(_samples + Dist2.samples());
        }
        
        /// @brief Subtract `Distribution`s by subtracting their samples element-wise.
        /// @param Dist2 the subtrahend.
        /// @return The resulting distribution.
        Distribution<T> operator- (const Distribution<T> Dist2) {
            return Distribution<T>(_samples - Dist2.samples());
        }
        
        /// @brief Multiply `Distribution`s by multiplying their samples element-wise.
        /// @param Dist2 the multiplier.
        /// @return The resulting distribution.
        Distribution<T> operator* (const Distribution<T> Dist2) {
            return Distribution<T>(_samples * Dist2.samples());
        }

        /// @brief Divide `Distribution`s by dividing their samples element-wise.
        /// @param Dist2 the divisor.
        /// @return The resulting distribution.
        Distribution<T> operator/ (const Distribution<T> Dist2) {
            return Distribution<T>(_samples / Dist2.samples());
        }

        // `Distribution`-scalar operations.

        /// @brief Sum of a `Distribution` and a scalar.
        /// @param scalar summand of type `T`.
        /// @return The resulting distribution.
        Distribution<T> operator+ (const T scalar) {
            return Distribution<T>(_samples + scalar);
        }

        /// @brief Subtract a `Distribution` by a scalar.
        /// @param scalar subtrahend of type `T`.
        /// @return The resulting distribution.
        Distribution<T> operator- (const T scalar) {
            return Distribution<T>(_samples - scalar);
        }

        /// @brief Multiply a `Distribution` by a scalar.
        /// @param scalar multiplier of type `T`.
        /// @return The resulting distribution.
        Distribution<T> operator* (const T scalar) {
            return Distribution<T>(_samples * scalar);
        }
        
        /// @brief Divide a `Distribution` by a scalar.
        /// @param scalar divisor of type `T`.
        /// @return The resulting distribution.
        Distribution<T> operator/ (const T scalar) {
            return Distribution<T>(_samples / scalar);
        }

        /// @brief Unary minus.
        /// @return The negated `Distribution`.
        Distribution<T> operator- () {
            return Distribution<T>(-1 * _samples);
        }

        // Friends
        template<typename> friend std::ostream& operator<< (std::ostream& os, const Distribution<T>);
        template<typename> friend Distribution<T> operator+ (T, const Distribution<T>);
        template<typename> friend Distribution<T> operator- (T, const Distribution<T>);
        template<typename> friend Distribution<T> operator* (T, const Distribution<T>);
        template<typename> friend Distribution<T> operator/ (T, const Distribution<T>);
};

// Friends

template <typename T>
std::ostream& operator<< (std::ostream& os, const Distribution<T>& Dist) {
    os << Dist.mean() << " +/- " << Dist.standard_deviation();
    return os;
}

// Scalar-`Distribution` operations.

/// @brief Add a `Distribution` to a scalar.
/// @tparam T the data type of the scalar and `Distribution`.
/// @param scalar the scalar of type `T` to multiply by.
/// @param Dist The `Distribution` to multiply by.
/// @return The resulting `Distribution`.
template <typename T>
Distribution<T> operator+ (T scalar, const Distribution<T>& Dist) {
    return Distribution<T>(scalar + Dist.samples());
}

/// @brief Subtract a scalar by a `Distribution`.
/// @tparam T the data type of the scalar and `Distribution`.
/// @param scalar the minuend of type `T`.
/// @param Dist The `Distribution` to subtract.
/// @return The resulting `Distribution`.
template <typename T>
Distribution<T> operator- (T scalar, const Distribution<T>& Dist) {
    return Distribution<T>(scalar - Dist.samples());
}

/// @brief Multiply a scalar by a `Distribution`.
/// @tparam T the data type of the scalar and  the samples in`Distribution`.
/// @param scalar the multiplicand of type `T`.
/// @param Dist The `Distribution` to multiply by.
/// @return The resulting `Distribution`
template <typename T>
Distribution<T> operator* (T scalar, const Distribution<T>& Dist) {
    return Distribution<T>(scalar * Dist.samples());
}

/// @brief Divide a scalar by a `Distribution`.
/// @tparam T the data type of the scalar and  the samples in`Distribution`.
/// @param scalar the dividend of type `T`.
/// @param Dist The `Distribution` to divide by.
/// @return The resulting `Distribution`.
template <typename T>
Distribution<T> operator/ (T scalar, const Distribution<T>& Dist) {
    return Distribution<T>(scalar / Dist.samples());
}

#endif
