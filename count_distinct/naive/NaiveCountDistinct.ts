import CountDistinctInterface from 'count_distinct/CountDistinctInterface';

class NaiveCountDistinct implements CountDistinctInterface {
  hashTable: { [key: string]: number };

  constructor() {
    this.hashTable = {};
  }

  add(element: string) {
    this.hashTable[element] = (this.hashTable[element] ?? 0) + 1;
  }

  count(): number {
    return Object.keys(this.hashTable).length;
  }
}

export default NaiveCountDistinct;
