part of sixstair;

typedef bool BrancherCallback(BrancherNode x);

class BrancherNode {
  final int depth;
  final bool hasMovedEmpty;
  final SixStair item;
  final String algorithm;
  
  BrancherNode(this.depth, this.item, this.algorithm,
      {bool movedEmpty: false}) : hasMovedEmpty = movedEmpty;
  
  SixStair copyItem() {
    return new SixStair.from(item);
  }
  
  Set<BrancherNode> expand() {
    Set<BrancherNode> nodes = new Set<BrancherNode>();
    nodes.add(new BrancherNode(depth + 1, copyItem()..flip(),
        '$algorithm F'));
    if (hasMovedEmpty) return nodes;
    if (item.topEmpty) {
      SixStair item = copyItem();
      for (int i = 1; i < 6; i++) {
        item.turn(1);
        var copy = new SixStair.from(item);
        nodes.add(new BrancherNode(depth + 1, copy, '$algorithm T$i',
            movedEmpty: true));
      }
    } else {
      SixStair item = copyItem();
      for (int i = 1; i < 6; i++) {
        item.turn(1);
        var copy = new SixStair.from(item);
        nodes.add(new BrancherNode(depth + 1, copy, '$algorithm T$i'));
      }
      item = copyItem();
      for (int i = 1; i < 6; i++) {
        item.turn(-1);
        var copy = new SixStair.from(item);
        nodes.add(new BrancherNode(depth + 1, copy, '$algorithm T-$i'));
      }
    }
    return nodes;
  }
}

class Brancher {
  int maxDepth;
  final SixStair start;
  
  Brancher(this.maxDepth, this.start) {
  }
  
  bool run(BrancherCallback f, [BrancherNode node = null]) {
    if (node == null) {
      return run(f, new BrancherNode(0, new SixStair.from(start), ''));
    }
    if (!f(node)) return false;
    if (node.depth < maxDepth) {
      for (BrancherNode n in node.expand()) {
        if (!run(f, n)) return false;
      }
    }
    return true;
  }
}
