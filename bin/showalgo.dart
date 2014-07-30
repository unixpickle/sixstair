#!/usr/bin/env dart

import '../lib/sixstair.dart';

void main(List<String> args) {
  Algorithm algo = new Algorithm.fromMoves(args);
  SixStair s = new SixStair.identity();
  algo.apply(s);
  print(s.toString());
}
