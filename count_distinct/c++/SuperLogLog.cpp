#include "SuperLogLog.hpp"

#include <vector>
#include <algorithm>

SuperLogLog::SuperLogLog(int K) : LogLog(K) {}

int SuperLogLog::count() {
    std::vector<int> mm;
    mm.resize(m, 0);
    for (int i = 0; i < m; ++i) mm[i] = M[i];

    sort(mm.begin(), mm.end());

    int cutoff = 0.70 * m;
    double z = 0;
    for (int i = 0; i < cutoff; ++i) z += M[i];
    z /= cutoff;

    return floor(0.5392 * cutoff * pow(2.0, z));
}