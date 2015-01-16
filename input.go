package sixstair

import (
	"errors"
	"fmt"
	"strconv"
)

// ReadState reads user input for a state.
func ReadState() (*State, error) {
	result := SolvedState()

	fmt.Println("Please ensure that no balls are in the top tubes.")
	for i := 0; i < 6; i++ {
		// Read the line
		fmt.Print("Enter tube " + strconv.Itoa(i+1) + ": ")
		var line string
		_, err := fmt.Scanln(&line)
		if err != nil {
			return nil, err
		}

		// Process the line
		nums, err := processLine(line, i)
		if err != nil {
			return nil, err
		}

		// Set the line in the puzzle
		copy(result.Bottom[i].Cells[:], nums)
		result.Bottom[i].Length = i + 1
	}
	return result, nil
}

func processLine(line string, idx int) ([]int, error) {
	runes := []rune(line)
	if len(runes) != idx+1 {
		return nil, errors.New("Invalid number of balls.")
	}

	// Read each rune and convert it to a color.
	res := make([]int, idx+1)
	for i, rune := range runes {
		// See if it's a numbered color.
		if rune >= '1' && rune <= '6' {
			res[i] = int(rune-'1') + 1
			continue
		}

		// Use special color characters.
		colors := "DWBYGR"
		found := false
		for c, x := range colors {
			if x == rune {
				res[i] = c + 1
				found = true
				break
			}
		}
		if !found {
			return nil, errors.New("Invalid character: " + string(rune))
		}
	}

	return res, nil
}
