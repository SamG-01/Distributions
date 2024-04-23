#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/Distribution.h"
#include "../include/RandomDistribution.h"

// Set fixed seed

std::mt19937 test_rng(0);

#define assertm(exp, msg) assert(((void)msg, exp))
#define asserteq(a, b, msg) assertm(std::abs(a - b) < 5e-6, msg)

int main() {
    // Constructors
    Distribution<double> N = Normal(2.0, 0.5, 1000, test_rng);
    Distribution<double> U = Uniform(3.0, 0.25, 1000, test_rng);

    // Getters
    asserteq(N.samples()[0], 2.5614, "Distribution<T>::samples()");
    asserteq(U.size(), 1000, "Distribution<T>::size()");
    asserteq(N.mean(), 2.00701, "Distribution<T>::mean()");
    asserteq(U.variance(), 0.614878, "Distribution<T>::variance()");
    asserteq(N.standard_deviation(), 0.509177, "Distribution<T>::standard_deviation()");
    asserteq(N[0], 2.5614, "Distribution<T>::operator[]");

    // Methods
    asserteq(N.apply(std::cos).average(), -0.372611, "Distribution<T>::apply()");
    asserteq(N.covariance(U), U.covariance(N), "Distribution<T>::covariance()");

    // Overloads
    asserteq((N + U).avg(), 3.60821, "Distribution<T>::operator+()");
    asserteq((U + 3.0).variance(), 0.614878, "Distribution<T>::operator+()");
    asserteq((2.0 + N).std_dev(), 0.509177, "T::operator+()");

    asserteq((N - U).mean(), 0.405811, "Distribution<T>::operator-()");
    asserteq((U - 3.0).var(), 0.614878, "Distribution<T>::operator-()");
    asserteq((-N).data()[0], -2.5614, "Distribution<T>operator-()");
    asserteq((2.0 - N).standard_deviation(), 0.509177, "T::operator-()");

    asserteq((N * U).average(), 3.19759, "Distribution<T>::operator*()");
    asserteq((U * 3.0).variance(), 5.5339, "Distribution<T>::operator*()");
    asserteq((2.0 * N).std_dev(), 1.01835, "T::operator*()");
    
    asserteq((N / U).avg(), 1.8448, "Distribution<T>::operator/()");
    asserteq((U / 3.0).var(), 0.0683198, "Distribution<T>::operator/()");
    asserteq((2.0 / N).standard_deviation(), 0.386532, "T::operator/()");

    std::ostringstream out;
    out << N;
    assertm(out.str() == "2.00701 +/- 0.509177", "std::ostream& operator<<");

    return 0;
}
