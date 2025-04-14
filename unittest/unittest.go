package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

const helpstr = `
unittest USAGE: unittest -i <input_file> -e <expected_string>`

const Reset = "\033[0m" 
const Red = "\033[31m" 
const Green = "\033[32m" 

type arguments struct {
	help bool
	input_file string
	expected_string string
	verbose bool
}

func parseArgs(args []string) (arguments, error) {
	if len(args) == 0 {
		return arguments{}, fmt.Errorf("no arguments provided")
	}

	arguments := arguments{} 
	for i := 0; i < len(args); i++ {
		switch args[i] {
		case "-h": 
			arguments.help = true
		case "-i":
			if i+1 >= len(args) {
				fmt.Println("Missing argument for -i")
				return arguments, fmt.Errorf("missing argument for -i")
			}
			arguments.input_file = args[i+1]
			i++
		case "-e":
			if i+1 >= len(args) {
				fmt.Println("Missing argument for -e")
				return arguments, fmt.Errorf("missing argument for -e")
			}
			arguments.expected_string = args[i+1]
			i++
		case "-v":
			arguments.verbose = true
		default: 
			fmt.Println("Unknown command: ", args[i])
			return arguments, fmt.Errorf("unknown command: %s", args[i])
		}
	}
	return arguments, nil
}

func argNotEmpty(arg string, message string) {
	if arg == "" {
		fmt.Println(message)
		os.Exit(1)
	}
}

func main() {
	arguments, err := parseArgs(os.Args[1:])

	if err != nil {
		fmt.Println(helpstr)
		os.Exit(1)
	}

	if arguments.help {
		fmt.Println()
		os.Exit(0)
	}

	argNotEmpty(arguments.input_file, "Missing input file. Run unittest -h for help.")
	argNotEmpty(arguments.expected_string, "Missing expected string. Run unittest -h for help.")
	
	// check if file exists
	if _, err := os.Stat(arguments.input_file); os.IsNotExist(err) {
		fmt.Println("File does not exist: ", arguments.input_file)
		os.Exit(1)
	}

	// read file
	file, err := os.Open(arguments.input_file)
	if err != nil {
		fmt.Println("Error opening file: ", arguments.input_file)
		os.Exit(1)
	}
	defer file.Close()

	if arguments.verbose {
		fmt.Println("input file ", arguments.input_file)
		fmt.Println("expected string ", arguments.expected_string)
	}

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()

		if arguments.verbose {
			fmt.Println("string ", arguments.expected_string)
		}	
		// if line contains expected string, print SUCCESS
		if strings.Contains(line, arguments.expected_string) {
			fmt.Println(Green + "SUCCESS" + Reset)
			os.Exit(0)
		}
	}
}
