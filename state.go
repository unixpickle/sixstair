package sixstair

// A State represents the state of a SixStair puzzle.
type State struct {
	Top     [6]*Tube
	Bottom  [6]*Tube
	Flipped bool
}

// SolvedState returns the solved SixStair.
func SolvedState() *State {
	s := State{}
	for i := 1; i <= 6; i++ {
		s.Top[i] = &Tube{Capacity: i, Length: 0}
		s.Bottom[i] = &Tube{Capacity: i, Length: i}
		for j := 0; j < i; j++ {
			s.Bottom[i].Cells[j] = i
		}
	}
	return &s
}

// A Tube is a single tube containing between 0 and six balls.
type Tube struct {
	Capacity int
	Cells    [6]int
	Length   int
}
