#!/usr/bin/env dart

import '../lib/sixstair.dart';
import 'dart:io';

void main(List<String> args) {
  if (args.length < 1) {
    print('Usage: dart bin/solvetube.dart <tube number> [<tube number> ...]');
    exit(1);
  }
  
  Set<int> tubes = new Set<int>();
  for (String a in args) {
    tubes.add(int.parse(a));
  }
  
  readSixStair().then((SixStair s) {
    print('solving: ${s.toString(spaces: 9)}');
    int depth = 0;
    while (true) {
      String solution = attemptSolve(s, depth, tubes);
      if (solution != null) {
        print('Solution: $solution');
        break;
      }
      depth++;
    }
  });
}

String attemptSolve(SixStair s, int depth, Set<int> tubes) {
  print('attempting depth $depth');
  String solution = null;
  new Brancher(depth, s).run((BrancherNode n) {
    if (n.depth < depth) return true;
    for (int tube in tubes) {
      if (!Checker.isTubeSolved(n.item, tube)) {
        return true;
      }
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
