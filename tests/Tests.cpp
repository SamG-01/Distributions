#include <cassert>
#include <iostream>
#include <string>

#include "../include/Distribution.h"
#include "../include/RandomDistribution.h"

// Set fixed seed

std::mt19937 test_rng(0);

#define assertm(exp, msg) assert((msg, exp))

int main() {
    // Constructors
    Distribution<double> N = Normal(2.0, 0.5, 1000, test_rng);
    Distribution<double> U = Uniform(3.0, 0.25, 1000, test_rng);

    // Getters
    assertm(N.samples()[0] == 2.5614, "Distribution.samples()");
    assertm(U.size() == 1000, "Distribution.size()");
    assertm(N.mean() == 2.00701, "Distribution.mean()");
    assertm(U.variance() == 0.0648154, "Distribution.variance()");
    assertm(N.standard_deviation() == 0.509177, "Distribution.standard_deviation()");
    assertm(N[0] == 2.5614, "Distribution.operator[]");

    return 0;
}
