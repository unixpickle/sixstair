part of sixstair;

class IndexNode extends LinkedListEntry {
  final int depth;
  final bool hasMovedEmpty;
  final SixStair item;
  
  IndexNode(this.depth, this.item, {bool movedEmpty: false}) :
    hasMovedEmpty = movedEmpty;
  
  SixStair copyItem() {
    return new SixStair.from(item);
  }
  
  Set<IndexNode> expand() {
    Set<IndexNode> nodes = new Set<IndexNode>();
    nodes.add(new IndexNode(depth + 1, copyItem()..flip()));
    if (hasMovedEmpty) return nodes;
    if (item.topEmpty) {
      SixStair item = copyItem();
      for (int i = 1; i < 6; i++) {
        item.turn(1);
        var copy = new SixStair.from(item);
        nodes.add(new IndexNode(depth + 1, copy, movedEmpty: true));
      }
    } else {
      SixStair item = copyItem();
      for (int i = 1; i < 6; i++) {
        item.turn(1);
        var copy = new SixStair.from(item);
        nodes.add(new IndexNode(depth + 1, copy));
      }
      item = copyItem();
      for (int i = 1; i < 6; i++) {
        item.turn(-1);
        var copy = new SixStair.from(item);
        nodes.add(new IndexNode(depth + 1, copy));
      }
    }
    return nodes;
  }
}

class Indexer {
  final LinkedList<IndexNode> nodes;
  int maxDepth;
  
  Indexer(this.maxDepth) : nodes = new LinkedList<IndexNode>() {
    nodes.add(new IndexNode(0, new SixStair.identity()));
  }
  
  IndexNode run() {
    if (nodes.length == 0) return null;
    IndexNode first = nodes.first;
    nodes.remove(nodes.first);
    if (first.depth < maxDepth) {
      for (IndexNode n in first.expand()) {
        nodes.add(n);
      }
    }
    return first;
  }
}
