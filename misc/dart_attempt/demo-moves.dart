import 'lib/sixstair.dart';

void main() {
  SixStair puzzle = new SixStair.identity();
  print('solved: ${puzzle.toString(spaces: 8)}');
  print('index: ${Hasher.chooseMajorPair(puzzle)}');
  
  puzzle.turn(1);
  print('turned: ${puzzle.toString(spaces: 8)}');
  print('index: ${Hasher.chooseMajorPair(puzzle)}');
  
  puzzle.flip();
  print('flipped: ${puzzle.toString(spaces: 9)}');
  print('index: ${Hasher.chooseMajorPair(puzzle)}');
}
