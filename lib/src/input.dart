part of sixstair;

Future<SixStair> readSixStair() {
  Completer<SixStair> comp = new Completer<SixStair>();
  
  int idx = 0;
  List<String> args = <String>[];
  
  var printFunc;
  printFunc = () {
    if (idx == 12) {
      return new Future(() {
        comp.complete(new SixStair.fromArgs(args));
      });
    }
    if (idx % 2 == 0) {
      stdout.write('Enter bottom of tube ${1 + idx ~/ 2}: ');
    } else {
      stdout.write('   Enter top of tube ${1 + idx ~/ 2}: ');
    }
    return stdout.flush().then((_) {
      ++idx;
      String line = stdin.readLineSync();
      if (line == null) {
        comp.completeError(new ArgumentError('premature EOF'));
        return null;
      }
      line = line.replaceAll('D', '1');
      line = line.replaceAll('W', '2');
      line = line.replaceAll('B', '3');
      line = line.replaceAll('Y', '4');
      line = line.replaceAll('G', '5');
      line = line.replaceAll('R', '6');
      args.add(line);
      return printFunc();
    });
  };
  
  printFunc().catchError(comp.completeError);
  
  return comp.future;
}