package sixstair

import (
	"sync"
)

// A Goal determines whether or not a state is "good" for a particular search.
type Goal interface {
	IsGoal(s *State) bool
}

// DistOptimal does exactly the same thing as Optimal, except it uses DistSearch
// instead of Search.
func DistOptimal(s *State, g Goal, max int) []Move {
	for i := 0; i <= max; i++ {
		if solution := DistSearch(s, g, i); solution != nil {
			return solution
		}
	}
	return nil
}

// DistSearch does exactly the same thing as Search, except it parallelizes the
// first layer of the search.
func DistSearch(s *State, g Goal, depth int) []Move {
	if depth <= 1 {
		return Search(s, g, depth)
	}
	
	moves := AllMoves()
	
	wg := sync.WaitGroup{}
	wg.Add(len(moves))
	
	var solution []Move
	var solutionLock sync.Mutex
	c := lockCanceller{}
	
	// Launch a goroutine for each move
	for _, move := range moves {
		go func(move Move) {
			puzzle := *s
			move.Apply(&puzzle)
			
			// Make sure the heuristics are passed correctly
			h := 1
			blockFlip := false
			if int(move) == 0 {
				h = 2
				blockFlip = true
			}
			
			if res := search(&puzzle, g, depth-1, h, blockFlip, c); res != nil {
				// Set the solution and cancel the other goroutines.
				solutionLock.Lock()
				solution = append([]Move{move}, res...)
				solutionLock.Unlock()
				c.Cancel()
			}
			wg.Done()
		}(move)
	}
	
	wg.Wait()
	return solution
}

// Optimal uses iterative deepening to find an optimal sequence of moves to get
// from a state to a goal.
// Like the Search method, this runs on a single goroutine.
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

// Search uses depth-first search to find a sequence of moves that arrives at a
// given goal from a starting state.
// The depth argument specifies the maximum number of moves to try.
// If no solution is found, nil is returned.
func Search(s *State, g Goal, depth int) []Move {
	return search(s, g, depth, 2, false, neverCanceller{})
}

func search(s *State, g Goal, depth int, h int, f bool, c canceller) []Move {
	// If we are at the goal, we found a trivial solution.
	if g.IsGoal(s) {
		return []Move{}
	}

	// If the maximum length is zero, there is no solution.
	if depth == 0 {
		return nil
	}

	// Perform a flip move if the last move was not a flip.
	if !f {
		state := *s
		state.Flip()
		if x := search(&state, g, depth-1, 2, true, c); x != nil {
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
		if depth >= 7 && c.Done() {
			return nil
		}
		state.Turn(true)
		if x := search(&state, g, depth-1, h-1, false, c); x != nil {
			return append([]Move{Move(i)}, x...)
		}
	}

	// Perform negative moves.
	state = *s
	for i := 1; i < 6; i++ {
		if depth >= 7 && c.Done() {
			return nil
		}
		state.Turn(false)
		if x := search(&state, g, depth-1, h-1, false, c); x != nil {
			return append([]Move{Move(-i)}, x...)
		}
	}

	return nil
}

type canceller interface {
	Done() bool
}

type neverCanceller struct{}

func (_ neverCanceller) Done() bool {
	return false
}

type lockCanceller struct {
	mutex sync.RWMutex
	done  bool
}

func (c lockCanceller) Cancel() {
	c.mutex.Lock()
	c.done = true
	c.mutex.Unlock()
}

func (c lockCanceller) Done() bool {
	c.mutex.RLock()
	defer c.mutex.RUnlock()
	return c.done
}
