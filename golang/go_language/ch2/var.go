package ch2

import "fmt"

/*
const a = 1
包级别声明:
	对于包含齐声明的源文件存在
	并且同一包的其他源文件也存在
*/
const varConst = 1
const VarConst = 2

/*
	声明通用格式
	var name type = expression
	type 或者expression 可以省略一个
*/

func TestVar() {
	var i, j, k int                 // int int int
	var b, f, s = true, 2.3, "four" // bool, float64 string

	fmt.Println(i, j, k, b, f, s)
}

/* 短声明
 */
func TestLiteVar() {
	i, j, k := 1, 2, 3

	/* 短声明，左值必须至少有一个新变量 */
	// i, j, k := 1, 2, 3 err

	fmt.Println(i, j, k)
}

func main() {
	TestVar()
}
