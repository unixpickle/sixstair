package sixstair

import (
	"errors"
	"sync"
)

// ErrNoSolution is returned by Search when no solution can be found.
var ErrNoSolution = errors.New("No solution found.")

// A Goal determines whether or not a state is "good" for a particular search.
type Goal interface {
	IsGoal(s *State) bool
}

// Search uses depth-first search to find a sequence of moves that arrives at a
// given goal from a starting state.
// The depth argument specifies the maximum number of moves to try.
// If no solution is found, ErrNoSolution is returned.
func Search(s *State, g Goal, depth int) ([]Move, error) {
	// If we are at the goal, we found a trivial solution.
	if g.IsGoal(s) {
		return []Move{}, nil
	}

	// If the maximum length is zero, there is no solution.
	if depth == 0 {
		return nil, ErrNoSolution
	}

	ch := make(chan []Move, 11)
	wg := sync.WaitGroup{}
	wg.Add(11)

	go func() {
		// Attempt a flip move to solve the puzzle.
		sCopy := s.Clone()
		sCopy.Flip()
		if moves := runBasicSearch(sCopy, g, depth-1); moves != nil {
			flip := Move{Flip: true}
			ch <- append([]Move{flip}, moves...)
		}
		wg.Done()
	}()

	// Perform various top rotations.
	for i := 1; i < 6; i++ {
		for j := 0; j < 2; j++ {
			go func(i int, j int) {
				move := Move{false, j == 0, i}
				sCopy := s.Clone()
				move.Apply(sCopy)
				if moves := runBasicSearch(sCopy, g, depth-1); moves != nil {
					ch <- append([]Move{move}, moves...)
				}
				wg.Done()
			}(i, j)
		}
	}

	// Wait for all the background routines to finish, then see if there's a
	// solution waiting for us.
	wg.Wait()
	close(ch)
	if solution := <-ch; solution != nil {
		return solution, nil
	}

	return nil, ErrNoSolution
}

// Optimal uses iterative deepening to find an optimal sequence of moves to get
// from a state to a goal.
// The max argument specifies the maximum number of moves to explore.
// If no solution is found, ErrNoSolution is returned.
func Optimal(s *State, g Goal, max int) ([]Move, error) {
	for i := 0; i <= max; i++ {
		solution, _ := Search(s, g, i)
		if solution != nil {
			return solution, nil
		}
	}
	return nil, ErrNoSolution
}

type basicSearch struct {
	max  int
	temp []*State
	goal Goal
}

func newBasicSearch(g Goal, depth int) *basicSearch {
	temp := make([]*State, depth)
	for i := 0; i < depth; i++ {
		temp[i] = SolvedState()
	}
	return &basicSearch{depth, temp, g}
}

func runBasicSearch(s *State, g Goal, maxDepth int) []Move {
	return newBasicSearch(g, maxDepth).Run(s, 0)
}

func (b *basicSearch) Run(s *State, depth int) []Move {
	// Check for the trivial solution.
	if b.goal.IsGoal(s) {
		return []Move{}
	}
	
	// Check if we can't search anymore.
	if depth == b.max {
		return nil
	}
	
	temp := b.temp[depth]
	CopyState(temp, s)
	
	// Attempt a flip move to solve the puzzle.
	temp.Flip()
	if moves := b.Run(temp, depth+1); moves != nil {
		flip := Move{Flip: true}
		return append([]Move{flip}, moves...)
	}

	// Perform various top rotations.
	for i := 1; i < 6; i++ {
		for j := 0; j < 2; j++ {
			move := Move{false, j == 0, i}
			CopyState(temp, s)
			move.Apply(temp)
			if moves := b.Run(temp, depth+1); moves != nil {
				return append([]Move{move}, moves...)
			}
		}
	}
	
	return nil
}
