import CountDistinctInterface from 'count_distinct/js/CountDistinctInterface';

class NaiveCountDistinct implements CountDistinctInterface {
  hashTable: { [key: string]: boolean } = {};

  size: number = 0;

  constructor() {}

  add(element: string) {
    if (this.hashTable[element]) return;

    this.hashTable[element] = true;
    this.size += 1;
  }

  count(): number {
    return this.size;
  }

  init() {
    this.size = 0;
    this.hashTable = {};
  }
}

export default NaiveCountDistinct;
