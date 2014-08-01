#!/usr/bin/env dart

import '../lib/sixstair.dart';
import 'dart:io';

void main(List<String> args) {
  if (args.length < 1) {
    print('Usage: dart bin/solvestep.dart <solve tube> [other ...]');
    exit(1);
  }
  
  int tube = int.parse(args[0]);
  Set<int> otherTubes = new Set<int>.from(args.map((x) => int.parse(x)));
  
  Set<SixStair> puzzles = new Set<SixStair>();
  readSixStair().then((SixStair s) {
    print('solving: ${s.toString(spaces: 9)}');
    Brancher.iterativeSearch(s, 15, (BrancherNode node) {
      if (!Checker.isTubeSolved(node.item, tube)) return true;
      if (puzzles.contains(node.item)) return true;
      puzzles.add(node.item);
      print('** found phase 1 solution: ${node.algorithm}');
      Brancher.iterativeSearch(node.item, 9, (BrancherNode inner) {
        if (Checker.areTubesSolved(inner.item, otherTubes)) {
          print('Tube solution: ${node.algorithm}');
          print('Rest solution: ${inner.algorithm}');
          exit(0);
        }
        return true;
      });
      print('** gave up!');
      return true;
    });
  });
}
