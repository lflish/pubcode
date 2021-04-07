package main

import (
	"./ch2"
	"./ch3"
	"fmt"
)

func test() {
	var i uint64
	for i = 0; i < 0x0f; i++ {
		fmt.Printf("PopCount:%x=%d\n", i, ch2.PopCount(i))
	}
}

func main() {
	//test()
	ch3.Test1()
}
