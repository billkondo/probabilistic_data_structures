class PolynomialHash {
  MOD: number;
  P: number;

  constructor(P = 53, MOD = 1e9 + 9) {
    this.P = P;
    this.MOD = MOD;
  }

  hash(s: string): number {
    let hash = 0;

    let p = 1;

    for (let i = 0; i < s.length; ++i) {
      const c = s.charCodeAt(i);

      hash = (hash + c * p) % this.MOD;
      p = (p * this.P) % this.MOD;
    }

    return hash;
  }
}

export default PolynomialHash;
