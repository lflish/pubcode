package main

/**
* @desc: 命令行参数
**/

import (
	"fmt"
	"os"
)

func show_args(){
	fmt.Println("arg[1:]:", os.Args[1:])
	fmt.Println("arg:", os.Args[:])
}

func main() {
	show_args()
}


