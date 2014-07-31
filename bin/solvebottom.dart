#!/usr/bin/env dart

import '../lib/sixstair.dart';
import 'dart:io';

void main(List<String> args) {
  if (args.length != 1) {
    print('Usage: dart bin/solvebottom.dart <bottom count>');
    exit(1);
  }
  
  int bottomCount = int.parse(args[0]);
  
  readSixStair().then((SixStair s) {
    print('using: ${s.toString(spaces: 7)}');
    int depth = 0;
    while (true) {
      String solution = attemptSolve(s, depth, bottomCount);
      if (solution != null) {
        print('Solution: $solution');
        break;
      }
      depth++;
    }
  });
}

String attemptSolve(SixStair s, int depth, int count) {
  print('attempting depth $depth');
  String solution = null;
  new Brancher(depth, s).run((BrancherNode n) {
    if (n.depth < depth) return true;
    if (n.item.isFlipped) return true;
    if (!n.item.isBottomSolved(count)) {
      return true;
    }
    if (n.algorithm.length > 0) {
      solution = n.algorithm.substring(1);
    } else {
      solution = '<no moves>';
    }
    return false;
  });
  return solution;
}
