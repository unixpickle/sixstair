package sixstair

import (
	"errors"
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

	// Attempt a flip move to solve the puzzle.
	sCopy := s.Clone()
	sCopy.Flip()
	if moves, _ := Search(sCopy, g, depth-1); moves != nil {
		flip := Move{Flip: true}
		return append([]Move{flip}, moves...), nil
	}

	// Perform various top rotations.
	for i := 1; i < 6; i++ {
		for j := 0; j < 2; j++ {
			move := Move{false, j == 0, i}
			sCopy = s.Clone()
			move.Apply(sCopy)
			if moves, _ := Search(sCopy, g, depth-1); moves != nil {
				return append([]Move{move}, moves...), nil
			}
		}
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
