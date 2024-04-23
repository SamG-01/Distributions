#include <cassert>
#include <iostream>
#include <string>

#include "../include/Distribution.h"
#include "../include/RandomDistribution.h"

// Set fixed seed

std::mt19937 test_rng(0);

/// @brief Runs a unit test using `assert`.
/// @param description A brief description of the test.
/// @param condition The test itself.
void unit_test(std::string description, bool condition) {
    std::cout << description << ": ";
    assert(condition);
    std::cout << "passed." << std::endl;
}

int main() {
    // Constructors
    Distribution<double> N = Normal(2.0, 0.5, 1000, test_rng);
    Distribution<double> U = Uniform(3.0, 0.25, 1000, test_rng);

    // Getters
    //unit_test("Distribution.samples()", N.samples()[0] == 1);
    unit_test("Distribution.num_samples()", U.num_samples() == 1000);
    unit_test("Distribution.mean()", N.mean() == 2.00701);
    unit_test("Distribution.variance()", U.variance() == 0.0648154);
    unit_test("Distribution.standard_deviation()", N.standard_deviation() == 1.509177);

    return 0;
}
