import CountDistinctInterface from 'count_distinct/CountDistinctInterface';

class NaiveCountDistinct implements CountDistinctInterface {
  hashTable: { [key: string]: boolean };

  size: number;

  constructor() {
    this.hashTable = {};
    this.size = 0;
  }

  add(element: string) {
    if (this.hashTable[element]) return;

    this.hashTable[element] = true;
    this.size += 1;
  }

  count(): number {
    return this.size;
  }
}

export default NaiveCountDistinct;
