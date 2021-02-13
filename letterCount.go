package main

import "fmt"

type letterCount struct {
	Letter byte
	Count  int
}

func main() {
	str1 := "aaabbcccca"
	str2 := ""
	str3 := "abcd"

	lca1 := findCount(str1)
	printStorage(lca1)

	lca2 := findCount(str2)
	printStorage(lca2)

	lca3 := findCount(str3)
	printStorage(lca3)
}

// findCount will receive a string as a parameter and
// return a slice of LetterCount structures/objects

func findCount(st string) []letterCount {
	letterCountStorage := []letterCount{}
	var i int
	for i < len(st) {
		tmp := st[i]
		j := 1
		for ; i+j < len(st) && tmp == st[i+j]; j++ {
		}
		letterCountStorage = append(letterCountStorage, letterCount{Letter: st[i], Count: j})
		i += j
	}
	return letterCountStorage
}

// output collected information

func printStorage(storage []letterCount) {
	fmt.Printf("[")
	for i, val := range storage {
		if i == len(storage)-1 { // for the last element do not print ", "
			fmt.Printf("{%q:%d}", val.Letter, val.Count)
		} else {
			fmt.Printf("{%q:%d}, ", val.Letter, val.Count)
		}
	}
	fmt.Printf("]\n")
}
