#pragma once
#include <cstdint>
#include <random>

namespace tractor {

struct Sample {
  double speed_kph{0.0};
  double rpm{0.0};
  double coolant_c{0.0};
};

class SensorSimulator {
 public:
  explicit SensorSimulator(std::uint32_t seed = 12345) : rng_(seed) {}

  Sample next() {
    std::normal_distribution<double> speed(8.0, 2.0);
    std::normal_distribution<double> rpm(1200.0, 200.0);
    std::normal_distribution<double> temp(85.0, 5.0);
    return Sample{ clamp(speed(rng_), 0.0, 40.0),
                   clamp(rpm(rng_), 600.0, 2400.0),
                   clamp(temp(rng_), 60.0, 120.0) };
  }

 private:
  static double clamp(double v, double lo, double hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
  }
  std::mt19937 rng_;
};

} // namespace tractor
