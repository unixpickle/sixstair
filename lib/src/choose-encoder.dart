part of sixstair;

/**
 * Generate [a] unordered-choose [b].
 */
int _choose(int a, int b) {
  // a!/(b!)(a - b)!
  int endFac = 1;
  for (int i = a; i > a - b; --i) {
   endFac *= i;
  }
  int bFac = 1;
  for (int i = 2; i <= b; i++) {
   bFac *= i;
  }
  return endFac ~/ bFac;
}

class ChooseEncoder {
  final List<bool> flags;
  int expected;
  
  ChooseEncoder(this.flags, this.expected);
  
  int generateHash() {
    if (flags.length == 0 || expected == 0) return 0;
    if (flags[flags.length - 1]) {
      flags.removeLast();
      --expected;
      return generateHash();
    } else {
      flags.removeLast();
      int missed = _choose(flags.length, expected - 1);
      return missed + generateHash();
    }
  }
}
