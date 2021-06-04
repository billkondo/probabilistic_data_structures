import HashFunctionType from 'count_distinct/js/HashFunctionType';
import LogLogCountDistinct from 'count_distinct/js/loglog/LogLogCountDistinct';

class HyperLogLogCountDistinct extends LogLogCountDistinct {
  constructor(k: number, hash: HashFunctionType) {
    super(k, hash);
  }

  alpha(): number {
    if (this.m == 16) return 0.673;
    if (this.m == 32) return 0.697;
    if (this.m == 64) return 0.709;
    return 0.7213 / (1 + 1.079 / this.m);
  }

  count(): number {
    let harnomic_mean = 0;

    for (let j = 0; j < this.m; ++j) {
      const x = 1 << this.M[j];
      harnomic_mean += 1 / x;
    }

    return Math.floor((this.alpha() * this.m * this.m) / harnomic_mean);
  }
}

export default HyperLogLogCountDistinct;
