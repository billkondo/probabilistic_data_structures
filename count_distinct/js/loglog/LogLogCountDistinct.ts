import CountDistinctInterface from 'count_distinct/js/CountDistinctInterface';
import HashFunctionType from 'count_distinct/js/HashFunctionType';

class LogLogCountDistinct implements CountDistinctInterface {
  hash: HashFunctionType = () => 1;
  k: number = 4;
  m: number = 1 << 4;
  M: { [key: number]: number } = {};
  A = 0.39701;
  mask: number = (1 << 4) - 1;

  constructor(k: number, hash: HashFunctionType) {
    if (k < 4) throw new Error('k should not be less than 4');

    this.k = k;
    this.m = 1 << k;
    this.hash = hash;
    this.mask = (1 << k) - 1;

    this.init();
  }

  _rank(x: number): number {
    let bit = 0;

    while (!((1 << bit) & x) && 1 << bit <= x) ++bit;

    return 1 + bit;
  }

  add(element: string) {
    const x = this.hash(element);
    const j = x & this.mask;
    const w = x >> this.k;

    this.M[j] = Math.max(this.M[j], this._rank(w));
  }

  count(): number {
    let arithmetic_mean = 0;

    for (let j = 0; j < this.m; j++) arithmetic_mean += this.M[j];

    arithmetic_mean /= this.m;

    return Math.floor(this.A * this.m * Math.pow(2, arithmetic_mean));
  }

  init() {
    this.M = {};
    for (let j = 0; j < this.m; ++j) this.M[j] = 0;
  }
}

export default LogLogCountDistinct;
