#include <valarray>
#include <cmath>

/// @brief Applies a supplied function to each element of a valarray.
/// @tparam T the element type.
/// @param arr the input valarray.
/// @param function the function to apply element-wise.
/// @return The valarray of function outputs.
template <typename T>
std::valarray<T> vapply(std::valarray<T> arr, auto (*function)(T)) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = function(arr[i]);
    }
    return arr;
}

/// @brief Finds the element-wise absolute value of a valarray.
/// @tparam T the element type.
/// @param arr the input valarray.
template <typename T>
std::valarray<T> vabs(std::valarray<T> arr) {
    return vapply(arr, std::abs)
}

/// @brief Finds the average of a valarray.
/// @tparam T the element type.
/// @param arr the input valarray.
template <typename T>
T vaverage(std::valarray<T> arr) {
    return arr.sum() / arr.size();
}

