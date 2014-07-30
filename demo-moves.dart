import 'lib/sixstair.dart';

void main() {
  SixStair puzzle = new SixStair.identity();
  print('solved: ${puzzle.toString(spaces: 8)}');
  
  puzzle.turn(1);
  print('turned: ${puzzle.toString(spaces: 8)}');
  
  puzzle.flip();
  print('flipped: ${puzzle.toString(spaces: 9)}');
}
