part of sixstair;

class Algorithm {
  List<Move> moves;
  
  Algorithm.fromMoves(List<String> ms) {
    moves = new List.from(ms.map((m) => new Move.fromString(m)));
  }
  
  Algorithm.fromString(String s) {
    List<String> moveStr = s.split(' ');
    moves = new List.from(moveStr.map((m) => new Move.fromString(m)));
  }
  
  void apply(SixStair s) {
    for (Move m in moves) {
      m.apply(s);
    }
  }
  
  String toString() {
    Iterable<String> strs = moves.map((x) => x.toString());
    return new List.from(strs).join(' ');
  }
}
