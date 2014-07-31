#!/usr/bin/env dart

import '../lib/sixstair.dart';
import 'dart:io';

void main(List<String> args) {
  if (args.length != 1) {
    print('Usage: dart bin/solvetube.dart <tube number>');
    exit(1);
  }
  
  int tubeNumber = int.parse(args[0]);
  
  readSixStair().then((SixStair s) {
    print('solving: ${s.toString(spaces: 9)}');
    int depth = 0;
    while (true) {
      String solution = attemptSolve(s, depth, tubeNumber);
      if (solution != null) {
        print('Solution: $solution');
        break;
      }
      depth++;
    }
  });
}

String attemptSolve(SixStair s, int depth, int tube) {
  print('attempting depth $depth');
  String solution = null;
  new Brancher(depth, s).run((BrancherNode n) {
    if (n.depth < depth) return true;
    if (n.item.isTubeSolved(tube)) {
      if (n.algorithm.length > 0) {
        solution = n.algorithm.substring(1);
      } else {
        solution = '<no moves>';
      }
      return false;
    }
    return true;
  });
  return solution;
}
