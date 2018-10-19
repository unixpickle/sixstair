# Goal

My goal is to programmatically solve the "SixStair" puzzle (picture below). I first attempted to write the [solver in Dart](old/dart_attempt), then I completed a solver in [C++](old/SixStairSolver).

The Go-based solver in the root of this repository (and in the `sixstair-` subdirectories) seems to work.

# Usage

Run `sixstair-solve` or `sixstair-phases` and follow the input directions. The resulting solution uses a move notation where `Tn` indicates to turn the top part of the puzzle clockwise `n` times. An `F` move indicates to flip the puzzle over.

# Picture

Here is the puzzle in all its glory:

![SixStair.jpg](misc/sixstair.png)
