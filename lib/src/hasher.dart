part of sixstair;

class Hasher {
  /**
   * Return a number which represents the layout of the [color] balls.
   * 
   * You may optionally ignore other colors for this index by passing a list of
   * colors to [ignore].
   */
  static int chooseColor(SixStair s, int color, {List<int> ignore: null}) {
    List<int> colors = s.toColorList(ignore: ignore);
    List<bool> flags = new List.from(colors.map((x) => x == color));
    return new _ChooseEncoder(flags, color).generateHash();
  }
  
  /**
   * Returns a number in the range (0, 162954791) which represents the layout of
   * the orange and green balls. This range is derived from the product of
   * (21 choose 6) and (15 choose 5).
   */
  static int chooseMajorPair(SixStair s) {
    return chooseColor(s, 6) * 3003 + chooseColor(s, 5, ignore: [6]);
  }
}