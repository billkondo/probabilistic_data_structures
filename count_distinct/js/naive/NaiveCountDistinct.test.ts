import NaiveCountDistinct from './NaiveCountDistinct';

test('Should count distinct elements', () => {
  const distinctCount = new NaiveCountDistinct();

  const data = ['a', 'b', 'c', 'd', 'e'];

  for (const element of data) distinctCount.add(element);
  for (const element of data) distinctCount.add(element);

  expect(distinctCount.count()).toBe(5);
});
