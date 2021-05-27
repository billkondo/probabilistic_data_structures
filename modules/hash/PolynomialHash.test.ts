import PolynomialHash from './PolynomialHash';

test('Polynomial hash with M = 53 and MOD = 1e9 + 9', () => {
  const polynomialHash = new PolynomialHash();
  const s = 'polynomial_hash';
  expect(polynomialHash.hash(s)).toBe(228921336);
});

test('Polynomial hash with M = 31 and MOD = 1e9 + 7', () => {
  const polynomialHash = new PolynomialHash(31, 1e9 + 7);
  const s = 'polynomial_hash';
  expect(polynomialHash.hash(s)).toBe(253665039);
});
