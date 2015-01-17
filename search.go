package sixstair

import (
	"sync"
)

// A Goal determines whether or not a state is "good" for a particular search.
type Goal interface {
	IsGoal(s *State) bool
}

// DistSearch does exactly the same thing as Search, except it parallelizes the
// first layer of the search.
func DistSearch(s *State, g Goal, depth int) []Move {
	moves := AllMoves()
	wg := sync.WaitGroup{}
	wg.Add(len(moves))
	solution := make(chan []Move, len(moves))
	for _, move := range moves {
		go func(move Move) {
			puzzle := *s
			if res := Search(&puzzle, g, depth-1); res != nil {
				solution <- res
			}
			wg.Done()
		}(move)
	}
	wg.Wait()
	return <-solution
}

// Search uses depth-first search to find a sequence of moves that arrives at a
// given goal from a starting state.
// The depth argument specifies the maximum number of moves to try.
// If no solution is found, nil is returned.
func Search(s *State, g Goal, depth int) []Move {
	return search(s, g, depth, 2, false)
}

// Optimal uses iterative deepening to find an optimal sequence of moves to get
// from a state to a goal.
// The max argument specifies the maximum number of moves to explore.
// If no solution is found, nil is returned.
func Optimal(s *State, g Goal, max int) []Move {
	for i := 0; i <= max; i++ {
		if solution := Search(s, g, i); solution != nil {
			return solution
		}
	}
	return nil
}

func search(s *State, g Goal, depth int, h int, f bool) []Move {
	// If we are at the goal, we found a trivial solution.
	if g.IsGoal(s) {
		return []Move{}
	}

	// If the maximum length is zero, there is no solution.
	if depth == 0 {
		return nil
	}

	// Perform a flip move.
	if !f {
		state := *s
		state.Flip()
		if x := search(&state, g, depth-1, 2, true); x != nil {
			return append([]Move{Move(0)}, x...)
		}
	}

	// If the last two moves were turns, the next move cannot be a turn as well.
	// TODO: make *sure* this is true.
	if h == 0 {
		return nil
	}

	// Perform positive moves.
	state := *s
	for i := 1; i < 6; i++ {
		state.Turn(true)
		if x := search(&state, g, depth-1, h-1, false); x != nil {
			return append([]Move{Move(i)}, x...)
		}
	}

	// Perform negative moves.
	state = *s
	for i := 1; i < 6; i++ {
		state.Turn(false)
		if x := search(&state, g, depth-1, h-1, false); x != nil {
			return append([]Move{Move(-i)}, x...)
		}
	}

	return nil
}
