#include <iostream>
#include <random>
#include <vector>
#include <standards/timer.hpp>
#include "walker/random_choice.hpp"

static const unsigned int n = 9;
static const unsigned int samples = 100000;

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

  for (auto n : sizes) {
    // generate weights
    std::vector<double> weights(n);
    for (auto& w : weights) w = dist(eng);

    // random_choice
    walker::random_choice<engine_type> rc(weights);

    // benchmark test
    auto r = rc(eng);
    int loop = 1;
    double elapsed = 0.0;
    for (; elapsed < duration && loop < (1 << 30); loop *= 2) {
      standards::timer t;
      for (int p = 0; p < loop; ++p) auto r = rc(eng);
      elapsed = t.elapsed();
    }

    if (r < 0 || r >= n) {
      std::cerr << "range error\n";
      std::exit(127);
    }

    auto perf = loop / elapsed;
    std::cout << n << ' ' << loop << ' ' << ' ' << elapsed << ' ' << perf << std::endl;
  }
}
