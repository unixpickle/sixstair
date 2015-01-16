package sixstair

import (
	"strconv"
)

// A State represents the state of a SixStair puzzle.
type State struct {
	Top     [6]*Tube
	Bottom  [6]*Tube
	Flipped bool
}

// SolvedState returns the solved SixStair.
func SolvedState() *State {
	s := State{}
	for i := 0; i < 6; i++ {
		s.Top[i] = &Tube{Capacity: i + 1, Length: 0}
		s.Bottom[i] = &Tube{Capacity: i + 1, Length: i + 1}
		for j := 0; j <= i; j++ {
			s.Bottom[i].Cells[j] = i + 1
		}
	}
	return &s
}

// Clone returns a deep copy of a state.
func (s *State) Clone() *State {
	c := &State{Flipped: s.Flipped}
	for i := 0; i < 6; i++ {
		x := *s.Top[i]
		c.Top[i] = &x
		y := *s.Bottom[i]
		c.Bottom[i] = &y
	}
	return c
}

// Flip turns the SixStair upside-down.
func (s *State) Flip() {
	s.Flipped = !s.Flipped

	// Three transformations get performed, all in one:
	// - Swap s.Top and s.Bottom
	// - Run Flip() on every tube
	// - Reverse s.Top and s.Bottom
	for i := 0; i < 6; i++ {
		s.Top[i].Flip()
		s.Bottom[5-i].Flip()
		s.Top[i], s.Bottom[5-i] = s.Bottom[5-i], s.Top[i]
	}

	s.gravity()
}

// String returns a human-readable ASCII-art version of the state.
func (s *State) String() string {
	str := ""

	// Stringify the top tubes
	for j := 0; j < 7; j++ {
		idx := 6 - j
		for i := 0; i < 6; i++ {
			t := s.Top[i]
			if t.Capacity == idx {
				str += " _ "
			} else if t.Capacity < idx {
				str += "   "
			} else if t.Length > idx {
				str += "|" + strconv.Itoa(t.Cells[idx]) + "|"
			} else {
				str += "| |"
			}
		}
		str += "\n"
	}

	str += "------------------\n"

	// Stringify the bottom tubes
	for idx := 0; idx < 7; idx++ {
		for i := 0; i < 6; i++ {
			t := s.Bottom[i]
			if t.Capacity == idx {
				str += " _ "
			} else if t.Capacity < idx {
				str += "   "
			} else if t.Length > idx {
				str += "|" + strconv.Itoa(t.Cells[idx]) + "|"
			} else {
				str += "| |"
			}
		}
		if idx != 6 {
			str += "\n"
		}
	}

	return str
}

// Turn turns the top tubes once in the given direction.
func (s *State) Turn(clockwise bool) {
	// Is this code nice? No. Is this code efficient? Possibly. Is this code
	// short and readable? YES!
	if clockwise {
		s.Top[0], s.Top[1], s.Top[2], s.Top[3], s.Top[4], s.Top[5] =
			s.Top[1], s.Top[2], s.Top[3], s.Top[4], s.Top[5], s.Top[0]
	} else {
		s.Top[1], s.Top[2], s.Top[3], s.Top[4], s.Top[5], s.Top[0] =
			s.Top[0], s.Top[1], s.Top[2], s.Top[3], s.Top[4], s.Top[5]
	}
	s.gravity()
}

func (s *State) gravity() {
	for i := 0; i < 6; i++ {
		top := s.Top[i]
		bottom := s.Bottom[i]
		for top.Length > 0 && bottom.Length < bottom.Capacity {
			bottom.Push(top.PopFront())
		}
	}
}

// A Tube is a single tube containing between 0 and six balls.
type Tube struct {
	Capacity int
	Cells    [6]int
	Length   int
}

// Flip reverses the contents of the tube.
func (t *Tube) Flip() {
	for i := 0; i < t.Length/2; i++ {
		swapIdx := t.Length - (i + 1)
		t.Cells[i], t.Cells[swapIdx] = t.Cells[swapIdx], t.Cells[i]
	}
}

// PopFront removes the first ball and returns it.
// The tube's length must be greater than 0.
func (t *Tube) PopFront() int {
	if t.Length == 0 {
		panic("PopFront() called on empty tube.")
	}
	res := t.Cells[0]
	copy(t.Cells[:t.Length], t.Cells[1:t.Length])
	t.Length--
	return res
}

// Push adds a ball to the end of the tube.
// The tube's length must be less than its capacity.
func (t *Tube) Push(ball int) {
	if t.Length == t.Capacity {
		panic("Push() called on full tube.")
	}
	t.Cells[t.Length] = ball
	t.Length++
}
