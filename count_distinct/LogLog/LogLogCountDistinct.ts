import CountDistinctInterface from 'count_distinct/CountDistinctInterface';
import HashFunctionType from 'count_distinct/HashFunctionType';

class LogLogCountDistinct implements CountDistinctInterface {
  hash: HashFunctionType;
  k: number;
  m: number;
  M: { [key: number]: number };
  A: number;

  constructor(k: number, hash: HashFunctionType) {
    if (k < 4) throw new Error('k should not be less than 4');

    this.k = k;
    this.m = 1 << k;

    this.hash = hash;

    this.M = {};
    for (let j = 0; j < 1 << k; ++j) this.M[j] = 0;

    this.A = this._estimateBias(this.m);
  }

  _estimateBias(m: number): number {
    if (m == 16) return 0.673;
    if (m == 32) return 0.697;
    if (m == 64) return 0.709;

    return 0.7213 / (1 + 1.079 / m);
  }

  _bucket(x: number): number {
    let bucket = 0;

    for (let bit = 0; bit < this.k; ++bit)
      if ((1 << bit) & x) bucket += 1 << bit;

    return bucket;
  }

  _rank(x: number): number {
    let bit;

    for (bit = 0; 1 << bit < x; ++bit) if ((1 << bit) & x) return bit;

    return bit;
  }

  add(element: string) {
    const x = this.hash(element);
    const j = this._bucket(x);
    const w = x >> this.k;

    this.M[j] = Math.max(this.M[j], 1 + this._rank(w));
  }

  count(): number {
    let arithmetic_mean = 0;

    for (let j = 0; j < this.m; j++) arithmetic_mean += this.M[j];

    arithmetic_mean /= this.m;

    return Math.floor(this.A * this.m * Math.pow(2, arithmetic_mean));
  }
}

export default LogLogCountDistinct;
