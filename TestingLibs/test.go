package main

import (
	"fmt"
	"os"
)

func main() {
	args := os.Args[1:]
	
	cmd := args[0]
	cmdArgs := args[1]
	input := args[2]

	fmt.Printf("Cmd: %s, cmdArgs: %s, Input: %s", cmd, cmdArgs, input)
}
