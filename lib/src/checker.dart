part of sixstair;

class Checker {
  static bool isTubeSolved(SixStair s, int size) {
    for (int i = 0; i < 6; i++) {
      if (s.bottomTubes[i].capacity != size) continue;
      return s.bottomTubes[i].solved;
    }
    return false;
  }

  static bool isBottomSolved(SixStair s, int count) {
    for (int i = 0; i < 6; i++) {
      Tube t = s.bottomTubes[i];
      int req = t.capacity > count ? count : t.capacity;
      if (req > t.length) return false;
      for (int j = 0; j < req; j++) {
        if (t[j] != t.capacity) return false; 
      }
    }
    return true;
  }

  static bool isSolvedUpTo(SixStair s, int maxTube) {
    for (int i = 0; i < 6; i++) {
      if (s.bottomTubes[i].capacity > maxTube) continue;
      if (!s.bottomTubes[i].solved) return false;
    }
    return true;
  }
  
  static bool areTubesSolved(SixStair s, Set<int> tubes) {
    for (int i = 0; i < 6; i++) {
      if (!tubes.contains(s.bottomTubes[i].capacity)) continue;
      if (!s.bottomTubes[i].solved) return false;
    }
    return true;
  }
}
