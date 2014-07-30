import 'lib/sixstair.dart';

void main() {
  SixStair puzzle = new SixStair.identity();
  print('solved: ${puzzle.toString(spaces: 8)}');
  print('index: ${puzzle.indexMajorPair()}');
  
  puzzle.turn(1);
  print('turned: ${puzzle.toString(spaces: 8)}');
  print('index: ${puzzle.indexMajorPair()}');
  
  puzzle.flip();
  print('flipped: ${puzzle.toString(spaces: 9)}');
  print('index: ${puzzle.indexMajorPair()}');
}
