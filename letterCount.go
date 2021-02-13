package main

import "fmt"

type LetterCount struct {
	Letter byte
	Count  int
}

func main() {
	str1 := "aaabbcccca"
	str2 := ""
	str3 := "abcd"

	lca1 := findCount(str1)
	lca2 := findCount(str2)
	lca3 := findCount(str3)

	printArray(lca1)
	printArray(lca2)
	printArray(lca3)
}

// findCount will receive astring as a parameter and return an
// return an array/slice of LetterCount structures/objects

func findCount(st string) []LetterCount {
	lcArray := []LetterCount{}
	var i int
	for i < len(st) {
		tmp := st[i]
		j := 1
		for ; i+j < len(st) && tmp == st[i+j]; j++ {
		}
		lcArray = append(lcArray, LetterCount{Letter: st[i], Count: j})
		i += j
	}
	return lcArray
}

func printArray(arr []LetterCount) {
	fmt.Printf("[")
	for _, val := range arr {
		fmt.Printf("{%q:%d} ", val.Letter, val.Count)
	}
	fmt.Printf("]\n")
}
