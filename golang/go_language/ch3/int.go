package ch3

import "fmt"

func Test1(){
	ascii := 'a'
	unicode := '国'
	newline := '\n'

	fmt.Printf("%d %[1]c, %[1]q\n", ascii);
	fmt.Printf("%d %[1]c, %[1]q\n", unicode);
	fmt.Printf("%d %[1]c, %[1]q\n", newline);
}
