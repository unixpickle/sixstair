#!/usr/bin/env dart

import '../lib/sixstair.dart';
import 'dart:io';

void main(List<String> args) {
  if (args.length != 2) {
    print('Usage: dart indexmajor.dart <max depth> <file>');
    exit(1);
  }
  String outputPath = args[1];
  RandomAccessFile f = new File(outputPath).openSync(mode: FileMode.APPEND);
  Indexer idx = new Indexer(int.parse(args[0]));
  int count = 0;
  while (true) {
    IndexNode node = idx.run();
    if (node == null) break;
    int hashIdx = node.item.indexChoose(6);
    if (node.depth == 0 || hashIdx == 0) continue;
    f.setPositionSync(hashIdx);
    int cur = f.readByteSync();
    if (cur == 0 && hashIdx != 0) {
      count++;
      f.writeByteSync(node.depth);
      if (count % 10 == 0) {
        print("indexed $count nodes");
      }
    }
  }
}
