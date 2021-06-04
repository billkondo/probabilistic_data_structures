#ifndef LOG_LOG_H
#define LOG_LOG_H

#include "DistincCountBase.hpp"
#include <vector>

struct LogLog : public DistinctCountBase {
  int K;
  int m;
  std::vector<int> M;
  int mask;

  double alpha = 0.39701;

  LogLog(int K);
  
  void add(int x);
  int count();

  int _rank(int x);
};

#endif