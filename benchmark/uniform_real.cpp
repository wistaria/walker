#include <iostream>
#include <random>
#include <vector>
#include <standards/timer.hpp>

int main(int argc, char** argv) {
  double duration;
  std::vector<int> sizes;
  if (argc == 2) {
    duration = std::atof(argv[1]);
  } else {
    std::cerr << "Error: " << argv[0] << " duration...\n";
    std::exit(127);
  }
  
  // random number generator
  typedef std::mt19937 engine_type;
  engine_type eng(29411);
  std::uniform_real_distribution<> rc;
  
  // benchmark test
  auto r = rc(eng);
  int loop = 1;
  double elapsed = 0.0;
  for (; elapsed < duration && loop < (1 << 30); loop *= 2) {
    standards::timer t;
    for (int p = 0; p < loop; ++p) r += rc(eng);
    elapsed = t.elapsed();
  }

  auto perf = loop / elapsed;
  r /= loop;
  std::cout << "# samples elapsed samples/sec average\n";
  std::cout << loop << ' ' << ' ' << elapsed << ' ' << perf << ' ' << r << std::endl;
}
