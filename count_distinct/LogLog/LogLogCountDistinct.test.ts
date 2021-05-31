import LogLogCountDistinct from './LogLogCountDistinct';

test('Should create 2^k registers', () => {
  const K = 10;
  const mockedHashFunction = () => 1;
  const countDistinct = new LogLogCountDistinct(K, mockedHashFunction);
  expect(Object.values(countDistinct.M).length).toBe(1 << K);
});
