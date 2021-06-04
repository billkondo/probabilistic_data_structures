#include "LogLog.hpp"

#include <vector>
#include <algorithm>
#include <cmath>

LogLog::LogLog(int K) : K(K) {
  m = (1 << K);
  M.resize(m, 0);

  mask = (1 << K) - 1;
}

int LogLog::_rank(int x) {
  int i = 0;
  while (!((1 << i) & x) && (1 << i) <= x) ++i;
  return i + 1;
}

void LogLog::add(int x) {
  int j = mask & x;
  int w = x >> K;

  M[j] = std::max(M[j], _rank(w));
}

int LogLog::count() {
  double z = 0;

  for (int i = 0; i < m; ++i)
    z += M[i];

  z /= m;
  
  return std::floor(alpha * m * std::pow(2.0, z));
}

