package sixstair

// A SolveGoal is only satisfied when a SixStair is completely solved.
type SolveGoal struct{}

// IsGoal returns true if the given state is entirely solved.
func (_ SolveGoal) IsGoal(s *State) bool {
	if s.Flipped {
		return false
	}

	// Make sure that:
	// - each tube has the right length
	// - each tube's balls are all the right color
	for i := 0; i < 6; i++ {
		tube := s.Bottom[i]
		if tube.Capacity != tube.Length {
			return false
		}
		for j := 0; j < tube.Length; j++ {
			if tube.Cells[j] != tube.Capacity {
				return false
			}
		}
	}

	return true
}

// A StepGoal is satisfied when the first N balls of a SixStair are solved,
// starting from the bottom of the biggest tube, going to the bottom of the next
// biggest tube, etc.
type StepGoal int

// IsGoal returns true if the given state has the first N balls solved, where N
// is int(goal).
func (goal StepGoal) IsGoal(s *State) bool {
	if s.Flipped {
		return false
	}

	var startIdx int
	for i := 0; i < 6; i++ {
		if s.Bottom[i].Capacity == 5 {
			startIdx = i
			break
		}
	}

	remaining := int(goal)
	for i := 0; i < 6 && remaining > 0; i++ {
		idx := startIdx - i
		if idx < 0 {
			idx += 6
		}
		tube := s.Bottom[idx]

		// If the tube could have more but doesn't, this is not the goal.
		if remaining > tube.Length && tube.Length < tube.Capacity {
			return false
		}

		// Make sure the tube contains balls of the correct color.
		for j := 0; j < tube.Length && remaining > 0; j++ {
			remaining--
			if tube.Cells[j] != 6-i {
				return false
			}
		}
	}

	return true
}
