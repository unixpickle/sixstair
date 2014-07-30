#!/usr/bin/env dart

import '../lib/sixstair.dart';
import 'dart:io';
import 'dart:typed_data';

void main(List<String> args) {
  if (args.length != 2) {
    print('Usage: dart indexmajor.dart <max depth> <file>');
    exit(1);
  }
  String outputPath = args[1];
  Uint8List buffer = new Uint8List(162954792);
  
  for (int i = 0; i < buffer.length; i++) {
    buffer[i] = 0xff;
  }
  
  Indexer idx = new Indexer(int.parse(args[0]));
  int count = 0;
  int nodeCount = 0;
  idx.run((IndexNode node) {
    nodeCount++;
    int hashIdx = node.item.indexMajorPair();
    if (hashIdx == 0) return;
    
    if (buffer[hashIdx] > node.depth) {
      buffer[hashIdx] = node.depth;
      count++;
      if (count % 1000 == 0) {
        print('set $count hashes [explored=$nodeCount]');
      }
    }
  });
  
  int hashCount = 0;
  for (int i = 0; i < buffer.length; i++) {
    if (buffer[i] < 0xff) {
      ++hashCount;
    }
  }
  
  print('found a total of $hashCount hashes');
  
  new File(outputPath).writeAsBytes(buffer).then((_) {
    print('wrote to ' + outputPath);
  }).catchError((e) {
    print('error writing file: $e');
  });
}
