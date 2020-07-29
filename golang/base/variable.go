package base

import "fmt"

//基本数据类型

func test_var(){

	//变量
	var x int = 100  // 等价于 x := 100
	var str string = "hello world"
	
	fmt.Println(x);
	fmt.Println(str);

	//常量
	const s string = "hello world"
	const pi float32 = 3.1415926

	//数组
	var arr [5] int
	fmt.Println("array arr:", arr);

	brr := [5] int {1,2,3,4,5}
	fmt.Println("array arr:", brr);
	//var c [2][3]int


	//数组切片
	a := [5]int{1, 2, 3, 4, 5}

	b := a[2:4]
	fmt.Println(b); //3 4

	b = a[0:4]
	fmt.Println(b); //1 2 3 4 

	b = a[2:]
	fmt.Println(b); //3 4 5

}