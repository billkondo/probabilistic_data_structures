#ifndef HYPER_LOG_LOG_H
#define HYPER_LOG_LOG_H

#include "LogLog.hpp"

struct HyperLogLog : public LogLog {
  double alpha();

  HyperLogLog(int K);
  int count();
};

#endif