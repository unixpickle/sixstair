part of sixstair;

class Tube {
  static const int BALL_BLACK = 1;
  static const int BALL_WHITE = 2;
  static const int BALL_BLUE = 3;
  static const int BALL_YELLOW = 4;
  static const int BALL_GREEN = 5;
  static const int BALL_RED = 6;
  
  final int capacity;
  final Uint8List balls;
  int length;
  
  bool get solved {
    if (length != capacity) return false;
    for (int i = 0; i < length; i++) {
      if (this[i] != capacity) return false;
    }
    return true;
  }
  
  Tube.empty(int cap) : capacity = cap, balls = new Uint8List(cap) {
    length = 0;
  }
  
  Tube.from(Tube t) : capacity = t.capacity, balls = new Uint8List(t.capacity) {
    length = 0;
    for (int i = 0; i < t.length; i++) {
      push(t[i]);
    }
  }
  
  int operator[](int idx) {
    assert(idx >= 0 && idx < length);
    return balls[idx];
  }
  
  void operator[]=(int idx, int value) {
    assert(idx >= 0 && idx < length);
    balls[idx] = value;
  }
  
  int pop() {
    assert(length > 0);
    return balls[--length];
  }
  
  int popFront() {
    assert(length > 0);
    int res = balls[0];
    for (int i = 0; i < length - 1; ++i) {
      balls[i] = balls[i + 1];
    }
    --length;
    return res;
  }
  
  void push(int x) {
    assert(length < capacity);
    balls[length++] = x;
  }
  
  void flip() {
    if (length == 0) return;
    for (int i = 0; i < length ~/ 2; ++i) {
      int temp = this[i];
      this[i] = this[length - 1 - i];
      this[length - 1 - i] = temp;
    }
  }
}
