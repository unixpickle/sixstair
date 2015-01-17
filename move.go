package sixstair

import (
	"strconv"
)

type Move int

func AllMoves() [11]Move {
	var res [11]Move
	for i := 1; i < 6; i++ {
		res[(i-1)*2] = Move(i)
	}
	res[10] = Move(0)
	return res
}

func (m Move) Apply(s *State) {
	if m == 0 {
		s.Flip()
	} else if m > 0 {
		for i := 0; i < int(m); i++ {
			s.Turn(true)
		}
	} else {
		for i := 0; i < -int(m); i++ {
			s.Turn(false)
		}
	}
}

func (m Move) String() string {
	if m == 0 {
		return "F"
	} else {
		return "T" + strconv.Itoa(int(m))
	}
}
