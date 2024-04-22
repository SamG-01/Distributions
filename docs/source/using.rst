***********
Using Distributions
***********

A ``Distribution`` contains a `valarray` of samplings from a distribution for the purpose of Monte Carlo error propagation. In particular, `RandomDistribution.h` contains functions that allow for the construction of these objects using common random distributions (e.g. normal, uniform).

.. code:: c++

   #include <iostream>

   #include "../include/RandomDistribution.h"

   int main() {
      // Set fixed seed

      std::mt19937 rng(0);

      // Define distributions of real numbers

      Distribution<double> x = Normal(2.0, 0.5, 1000, rng);
      Distribution<double> y = Normal(3.0, 0.25, 1000, rng);
      
      std::cout << "x = " << x << std::endl;  // 2.00701 +/- 0.509177
      std::cout << "y = " << y << "\n" << std::endl; // 3.00351 +/- 0.254589

      // Perform math

      Distribution<double> z = x * y.apply(std::cos);

      std::cout << "z = " << z << std::endl; // -1.94326 +/- 0.534799
      std::cout << "z*z = " << z*z << std::endl; // 4.06226 +/- 1.97789
      std::cout << "cov(z, x) = " << z.covariance(x) << std::endl; // -0.270275
   }
