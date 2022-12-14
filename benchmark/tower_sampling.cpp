#include <iostream>
#include <random>
#include <vector>
#include <standards/timer.hpp>
#include "walker/tower_sampling.hpp"

int main(int argc, char** argv) {
  double duration;
  std::vector<int> sizes;
  if (argc >= 3) {
    duration = std::atof(argv[1]);
    for (int i = 2; i < argc; ++i) sizes.push_back(std::atoi(argv[i]));
  } else {
    std::cerr << "Error: " << argv[0] << " duration size0...\n";
    std::exit(127);
  }
  
  // random number generator
  typedef std::mt19937 engine_type;
  engine_type eng(29411);
  std::uniform_real_distribution<> dist;

  std::cout << "# n samples elapsed samples/sec xor\n";
  for (auto n : sizes) {
    // generate weights
    std::vector<double> weights(n);
    for (auto& w : weights) w = dist(eng);

    // random_choice
    walker::tower_sampling<> rc(weights.begin(), weights.end());

    // benchmark test
    auto r = rc(eng);
    int loop = 1;
    double elapsed = 0.0;
    for (; elapsed < duration && loop < (1 << 30); loop *= 2) {
      standards::timer t;
      for (int p = 0; p < loop; ++p) r ^= rc(eng);
      elapsed = t.elapsed();
    }

    auto perf = loop / elapsed;
    std::cout << n << ' ' << loop << ' ' << ' ' << elapsed << ' ' << perf << ' ' << r << std::endl;
  }
}
