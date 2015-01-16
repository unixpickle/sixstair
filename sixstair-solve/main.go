package main

import (
	"fmt"
	"github.com/unixpickle/sixstair"
	"os"
	"runtime"
	"strconv"
)

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	
	state, err := sixstair.ReadState()
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	
	goal := sixstair.SolveGoal{}
	for moves := 0;; moves++ {
		fmt.Println("Trying", moves, "moves...")
		solution, _ := sixstair.Search(state, goal, moves)
		if solution != nil {
			// We're done
			fmt.Println("Found solution:", solution, "(" +
				strconv.Itoa(len(solution)), "moves)")
			return
		}
	}
}
