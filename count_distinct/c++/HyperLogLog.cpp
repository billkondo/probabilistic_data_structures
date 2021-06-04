#include "HyperLogLog.hpp"
#include <cmath>

HyperLogLog::HyperLogLog(int K) : LogLog(K) {}

double HyperLogLog::alpha() {
  if (m == 16) return 0.673;
  if (m == 32) return 0.697;
  if (m == 64) return 0.709;
  return 0.7213 / (1 + 1.079 / (double)m);
}

int HyperLogLog::count() {
  double z = 0;

  for (int i = 0; i < m; ++i)
    z += std::pow(2, -M[i]);

  return std::floor(1.0 * alpha() * m * m / z);
}