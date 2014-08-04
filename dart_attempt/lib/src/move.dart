part of sixstair;

abstract class Move {
  static const FLIP = const Flip();
  
  factory Move.fromString(String s) {
    if (s == 'F') {
      return FLIP;
    }
    Match m = new RegExp(r'^T(-?[1-6])$').matchAsPrefix(s);
    if (m == null) throw new ArgumentError('invalid move: $s');
    return new Turn(int.parse(m[1]));
  }
  
  void apply(SixStair s);
}

class Turn implements Move {
  final int turns;
  
  const Turn(this.turns);
  
  void apply(SixStair s) {
    if (turns > 0) {
      for (int i = 0; i < turns; i++) {
        s.turn(1);
      }
    } else {
      for (int i = 0; i < -turns; i++) {
        s.turn(-1);
      }
    }
  }
  
  String toString() {
    return 'T$turns';
  }
}

class Flip implements Move {
  const Flip();
  
  void apply(SixStair s) {
    s.flip();
  }
  
  String toString() {
    return 'F';
  }
}
