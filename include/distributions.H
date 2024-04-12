#include <valarray>
#include <iostream>
#include <cmath>
#include <functional>

template <typename T>
std::valarray<T> valarray_apply(std::valarray<T> arr, T (*function)(T)) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = function(arr[i]);
    }
    return arr;
}

template <typename T>
class distribution {
    private:
        // Essential Data
        std::valarray<T> _samples;
        int _num_samples;

        // Statistics
        T _mean;
        T _variance;
        T _stdev;

    public:
        // Constructors
        distribution(std::valarray<T> __samples) {
            _samples = __samples;
            _num_samples = __samples.size();

            _mean = __samples.sum() / _num_samples;
            _variance = (std::pow(valarray_apply<T>(__samples - _mean, std::abs), 2)).sum() / / _num_samples;
            _stdev = std::sqrt(_variance);
        };

        // Getters
        std::valarray<T> samples() const {
            return _samples;
        }
        int num_samples const {
            return _num_samples;
        }
        int length() const { return num_samples(); }
        int N() const { return num_samples(); }

        T mean() const {
            return _mean;
        }
        T average() const { return mean(); }
        T avg() const { return mean(); }
        T m() const { return mean(); }

        T variance() const {
            return _variance;
        }
        T var() const { return variance(); }

        T stdev() const {
            return _stdev;
        }
        T standard_deviation() const { return stdev(); }
        T error() const { return stdev(); }
        T s() const { return stdev(); }

        // TODO: cout
};
