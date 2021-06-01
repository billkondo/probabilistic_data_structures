#include "../../modules/json.hpp"

#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

using Json = nlohmann::json;

void print_binary(int x, int k = 32) {
  for (int i = 1; i <= k; ++i) {
    printf("%d", x % 2);
    x /= 2;
  }
  printf("\n");
}

struct Naive {
  set<int> M;

  Naive() {}

  void add(int x) {
    M.insert(x);
  }

  int count() {
    return M.size();
  }
};

struct LogLog {
  int K;
  int m;
  vector<int> M;
  int mask;

  double alpha = 0.39701;

  LogLog(int K) : K(K) {
    m = (1 << K);
    M.resize(m, 0);
    
    mask = 0;
    for (int i = 0; i < K; ++i)
      mask += (1 << i);
  }

  int rank(int x) {
    int i = 0;
    while (!((1 << i) & x) && (1 << i) <= x) ++i;
    return i + 1;
  }

  void add(int x) {
    int j = mask & x;
    int w = x >> K;

    M[j] = max(M[j], rank(w));
  }

  int count() {
    double z = 0;
    for (int i = 0; i < m; ++i)
      z += M[i];
    z /= m;
    return floor(alpha * m * pow(2.0, z));
  }
};

double relative_error(double a, double b) {
  return abs(b - a) / b;
}

int main() {
  int N = 5e4;
  int NMax = 1e9;
  int M = 5e4;

  srand(time(NULL));

  map<int, int> frequencies;

  for (int i = 1; i <= M; ++i) {
    Naive naive = Naive();
    LogLog loglog = LogLog(8);

    while (naive.count() < N) {
      int x = rand() % NMax;

      naive.add(x);
      loglog.add(x);
    }

    if (i % 50 == 0)
      cout << i << "/" << M << "\n";

    int y = loglog.count();
    if (frequencies.find(y) == frequencies.end()) 
      frequencies[y] = 1;
    else 
      frequencies[y] += 1;
  }

  Json json;
  for (auto f: frequencies) json[to_string(f.first)] = f.second;

  ofstream json_file("data.json");
  json_file << setw(2) << json << endl;


  return 0;
}