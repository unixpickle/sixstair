part of sixstair;

class SixStair {
  List<Tube> topTubes;
  List<Tube> bottomTubes;
  
  bool get topEmpty {
    for (int i = 0; i < topTubes.length; i++) {
      if (topTubes[i].length != 0) return false; 
    }
    return true;
  }
  
  /**
   * Create a solved and upright [SixStair].
   */
  SixStair.identity() : topTubes = [], bottomTubes = [] {
    for (int i = 1; i <= 6; ++i) {
      topTubes.add(new Tube.empty(i));
      bottomTubes.add(new Tube.empty(i));
      for (int j = 0; j < i; j++) {
        bottomTubes[i - 1].push(i);
      }
    }
  }
  
  /**
   * Deep-copy a [SixStair] object.
   */
  SixStair.from(SixStair s) : topTubes = [], bottomTubes = [] {
    for (int i = 0; i < 6; ++i) {
      topTubes.add(new Tube.from(s.topTubes[i]));
      bottomTubes.add(new Tube.from(s.bottomTubes[i]));
    }
  }
  
  /**
   * Create [SixStair] from command-line arguments. The arguments go from the
   * smallest tubes to the largest tubes. The first argument is the bottom
   * tube, then the top tube, etc.
   */
  SixStair.fromArgs(List<String> args) : topTubes = [], bottomTubes = [] {
    if (args.length != 12) throw new RangeError('SixStair requires 12 args');
    for (int i = 0; i < 12; i++) {
      String arg = args[i];
      if (arg.length > (i + 2) ~/ 2) {
        throw new RangeError('excessive balls in well $i');
      }
      Tube t = new Tube.empty(i + 1);
      for (int j = 0; j < args.length; j++) {
        int num = int.parse(args[0]);
        if (num < 1 || num > 6) {
          throw new RangeError('invalid color: $num');
        }
        t.push(num);
      }
      if (i % 2 == 0) {
        bottomTubes[i ~/ 2] = t;
      } else {
        topTubes[i ~/ 2] = t;
      }
    }
    
    _validate();
  }
  
  /**
   * Turn the top clockwise [rotations] times before applying gravity.
   */
  void turn(int rotations) {
    if (rotations < 0) return turn(6 + rotations);
    List<Tube> oldTop = new List.from(topTubes);
    for (int i = 0; i < 6; i++) {
      topTubes[i] = oldTop[(i + rotations) % 6];
    }
    _applyGravity();
  }
  
  /**
   * Perform a flip around the z-axis.
   */
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
  
  /**
   * Return a number which represents the layout of the [color] balls.
   * 
   * You may optionally ignore other colors for this index by passing a list of
   * colors to [ignore].
   */
  int indexChoose(int color, {List<int> ignore: null}) {
    List<int> colors = toColorList(ignore: ignore);
    List<bool> flags = new List.from(colors.map((x) => x == color));
    return new _ChooseEncoder(flags, color).generateHash();
  }
  
  /**
   * Returns a number in the range [0, 162954791] which represents the layout of
   * the orange and green balls. This range is derived from the product of
   * (21 choose 6) and (15 choose 5).
   */
  int indexMajorPair() {
    return indexChoose(6) * 3003 + indexChoose(5, ignore: [6]);
  }
  
  /**
   * Generate an ordered list of colors. The list simply iterates through the
   * colors in each tube starting with the top left-most tube, moving to the
   * bottom leftmost tube, etc.
   * 
   * This is useful for generating indexes.
   */
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
  
  /**
   * Dump a [SixStair] to a visual, ASCII-art style representation. The
   * resultant puzzle may look something like this:
   *
   *      _                
   *     | | _             
   *     |6|| | _          
   *     |6|| || | _       
   *     |6|| || || | _    
   *     |6|| || || || | _ 
   *     |6|| || || || || |
   *     ------------------
   *     |6|| || || || || |
   *      - |5||4||3||2||1|
   *        |5||4||3||2| - 
   *        |5||4||3| -    
   *        |5||4| -       
   *        |5| -          
   *         -
   *              
   */
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
  
  void _validate() {
    Map<int, int> counts = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0};
    for (int num in toColorList()) {
      ++counts[num];
    }
    for (int i = 1; i <= 6; i++) {
      if (counts[i] != i) {
        throw new StateError('invalid number (${counts[i]}) of color $i');
      }
    }
  }
}
