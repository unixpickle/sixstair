package main

import (
	"fmt"
	"github.com/unixpickle/sixstair"
	"os"
	"runtime"
)

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	state, err := sixstair.ReadState()
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	
	for progress := 1; progress < 22; progress++ {
		fmt.Print("Doing ", progress, " ... ")
		goal := sixstair.BackStepGoal(progress)
		opt := sixstair.DistOptimal(state, goal, 12)
		if opt == nil {
			fmt.Println("Failed. No solution <= 12 moves.")
			return
		}
		fmt.Println(opt)
		applyMoves(state, opt)
	}
}

func applyMoves(s *sixstair.State, moves []sixstair.Move) {
	for _, m := range moves {
		m.Apply(s)
	}
}
