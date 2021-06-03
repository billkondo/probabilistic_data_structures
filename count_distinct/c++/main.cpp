#include "../../modules/json.hpp"

#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <pthread.h>

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

struct SuperLogLog : public LogLog {
  double modified_alpha;

  SuperLogLog(int k) : LogLog(k) {
    modified_alpha = 0.47221;
  }

  int count() {
    vector<int> mm;
    mm.resize(m, 0);
    for (int i = 0; i < m; ++i) mm[i] = M[i];

    sort(mm.begin(), mm.end());

    int cutoff = 0.70 * m;
    double z = 0;
    for (int i = 0; i < cutoff; ++i) z += M[i];
    z /= cutoff;

    return floor(0.5392 * cutoff * pow(2.0, z));
  }
};

double relative_error(double a, double b) {
  return abs(b - a) / b;
}

struct work_data {
  int N;
  int M;
  int NMax;
  map<int, int> *frequencies;
};

void* work(void *args) {
  struct work_data *thread_data;

  thread_data = (struct work_data *) args;  

  int N = thread_data->N;
  int M = thread_data->M;
  int NMax = thread_data->NMax;
  map<int, int> *frequencies = thread_data->frequencies;

  for (int i = 1; i <= M; ++i) {
    Naive naive = Naive();
    SuperLogLog loglog = SuperLogLog(8);

    while (naive.count() < N) {
      int x = rand() % NMax;

      naive.add(x);
      loglog.add(x);
    }

    if (i % 50 == 0)
      cout << i << "/" << M << "\n";

    int y = loglog.count();
    if ((*frequencies).find(y) == (*frequencies).end()) 
      (*frequencies)[y] = 1;
    else 
      (*frequencies)[y] += 1;
  }

  pthread_exit(NULL);
}

int main() {
  int N = 5e4;
  int NMax = 1e9;
  int M = 5e4;

  srand(time(NULL));
  
  int Threads = 4;

  pthread_t threads[Threads];
  struct work_data data[Threads];
  map<int, int> work_frequencies[Threads];

  for (int i = 0; i < Threads; ++i) {
    data[i].M = M / Threads;
    data[i].N = N;
    data[i].NMax = NMax;
    data[i].frequencies = &work_frequencies[i];

    int rc = pthread_create(&threads[i], NULL, work, (void *)&data[i]);
    if (rc) {
      cout << "Unable to create thread: " << rc << "\n";
      exit(-1);
    }
  }

  map<int, int> frequencies;

  void* status;
  for (int i = 0; i < Threads; ++i) {
    int rc = pthread_join(threads[i], &status);
    if (rc) {
      cout << "Unable to join thread: " << rc << "\n";
      exit(-1);
    }
  }

  for (int i = 0; i < Threads; ++i)
    for (auto p: work_frequencies[i])
      if (frequencies.find(p.first) == frequencies.end()) 
        frequencies[p.first] = p.second;
      else
        frequencies[p.first] += p.second;

  Json json;
  for (auto f: frequencies) json[to_string(f.first)] = f.second;

  ofstream json_file("data.json");
  json_file << setw(2) << json << endl;

  pthread_exit(NULL);
}