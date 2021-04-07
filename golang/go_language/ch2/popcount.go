package ch2

import "fmt"

var pc [256]byte

/* 创建bitmap */
func init() {
	for i := range pc {
		//for i, _:= range pc{ /* 也可以用这种方式 */
		pc[i] = pc[i/2] + byte(i&1)
		fmt.Printf("%d %d %d %d\n", i, pc[i], pc[i/2], byte(i&1))
	}
	fmt.Printf("\n")
}

func PopCount(x uint64) int {
	fmt.Printf("2\n")
	return int(pc[byte(x>>(0*8))] +
		pc[byte(x>>(1*8))] +
		pc[byte(x>>(2*8))] +
		pc[byte(x>>(3*8))] +
		pc[byte(x>>(4*8))] +
		pc[byte(x>>(5*8))] +
		pc[byte(x>>(6*8))] +
		pc[byte(x>>(7*8))])
}
