part of sixstair;

class SixStair {
  List<Tube> topTubes;
  List<Tube> bottomTubes;
  
  SixStair.identity() : topTubes = [], bottomTubes = [] {
    for (int i = 1; i <= 6; ++i) {
      topTubes.add(new Tube.empty(i));
      bottomTubes.add(new Tube.empty(i));
      for (int j = 0; j < i; j++) {
        bottomTubes[i - 1].push(i);
      }
    }
  }
  
  SixStair.from(SixStair s) : topTubes = [], bottomTubes = [] {
    for (int i = 0; i < 6; ++i) {
      topTubes.add(new Tube.from(s.topTubes[i]));
      bottomTubes.add(new Tube.from(s.bottomTubes[i]));
    }
  }
  
  void turn(int rotations) {
    List<Tube> oldTop = new List.from(topTubes);
    for (int i = 0; i < 6; i++) {
      topTubes[i] = oldTop[(i + rotations) % 6];
    }
    _applyGravity();
  }
  
  void flip() {
    // flip around x axis
    List<Tube> tempTop = topTubes;
    topTubes = bottomTubes;
    bottomTubes = tempTop;
    for (int i = 0; i < 6; i++) {
      topTubes[i].flip();
      bottomTubes[i].flip();
    }
    
    // flip around y axis
    for (int i = 0; i < 3; i++) {
      Tube temp = topTubes[i];
      topTubes[i] = topTubes[5 - i];
      topTubes[5 - i] = temp;
      
      temp = bottomTubes[i];
      bottomTubes[i] = bottomTubes[5 - i];
      bottomTubes[5 - i] = temp;
    }
    
    _applyGravity();
  }
  
  int indexChoose(int color, {List<int> ignore: null}) {
    List<int> colors = toColorList(ignore: ignore);
    List<bool> flags = new List.from(colors.map((x) => x == color));
    return new ChooseEncoder(flags, color).generateHash();
  }
  
  List<int> toColorList({List<int> ignore: null}) {
    List<int> colors = new List<int>();
    for (int i = 0; i < 6; i++) {
      List<Tube> ts = [topTubes[i], bottomTubes[i]];
      for (Tube t in ts) {
        for (int j = 0; j < t.length; j++) {
          int color = t[j];
          if (ignore == null || !ignore.contains(color)) {
            colors.add(color);
          }
        }        
      }
    }
    return colors;
  }
  
  String toString({String newLineStr: '\n', int spaces: 0}) {
    String newLine = newLineStr;
    for (int i = 0; i < spaces; i++) {
      newLine += ' ';
    }
    
    StringBuffer buffer = new StringBuffer();
    
    // print the top tubes
    for (int j = 0; j < 7; ++j) {
      int idx = 6 - j;
      for (int i = 0; i < 6; ++i) {
        Tube t = topTubes[i];
        if (t.capacity == idx) {
          buffer.write(' _ ');
        } else if (t.capacity < idx) {
          buffer.write('   ');
        } else if (t.length > idx) {
          buffer.write('|${t[i]}|');
        } else {
          buffer.write('| |');
        }
      }
      buffer.write(newLine);
    }
    
    buffer.write('------------------$newLine');
    
    // print the bottom tubes
    for (int idx = 0; idx < 7; ++idx) {
      for (int i = 0; i < 6; i++) {
        Tube t = bottomTubes[i];
        int baseIdx = t.capacity - idx - 1;
        if (t.capacity == idx) {
          buffer.write(' - ');
        } else if (t.capacity < idx) {
          buffer.write('   ');
        } else if (t.length > baseIdx) {
          buffer.write('|${t[baseIdx]}|');
        } else {
          buffer.write('| |');
        }
      }
      buffer.write(newLine);
    }
    
    return buffer.toString();
  }
  
  void _applyGravity() {
    for (int i = 0; i < 6; i++) {
      Tube top = topTubes[i];
      Tube bottom = bottomTubes[i];
      while (top.length > 0 && bottom.length < bottom.capacity) {
        bottom.push(top.popFront());
      }
    }
  }
}
