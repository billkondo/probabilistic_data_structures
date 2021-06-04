#ifndef SUPER_LOG_LOG_H
#define SUPER_LOG_LOG_H

#include "LogLog.hpp"

struct SuperLogLog : public LogLog {
  SuperLogLog(int K);
  
  int count();
};

#endif