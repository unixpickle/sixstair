package sixstair

import (
	"strconv"
)

type Move struct {
	Flip      bool
	Clockwise bool
	Count     int
}

func AllMoves() []*Move {
	res := make([]*Move, 1, 11)
	res[0] = &Move{Flip: true}
	for i := 1; i < 6; i++ {
		res = append(res, &Move{false, true, i}, &Move{false, false, i})
	}
	return res
}

func (m *Move) Apply(s *State) {
	if m.Flip {
		s.Flip()
		return
	}
	for i := 0; i < m.Count; i++ {
		s.Turn(m.Clockwise)
	}
}

func (m *Move) String() string {
	if m.Flip {
		return "F"
	} else if m.Clockwise {
		return "T" + strconv.Itoa(m.Count)
	} else {
		return "T-" + strconv.Itoa(m.Count)
	}
}
