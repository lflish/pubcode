package base

// 流程控制

import "fmt"

/*注意：
	if 语句没有圆括号，而必需要有花括号
	if,else有换行格式要求
*/
func TestIf(){
	var x int = 8

	if x % 2 == 0{
		fmt.Println(x, "是偶数");
	}

	if x % 2 == 0{
		fmt.Println(x, "是偶数");
	}else {
		fmt.Println(x, "是奇数");
	}

	if x % 2 == 0{
		fmt.Println(x, "是偶数");
	} else if x == 0{
		fmt.Println(x, "是0");
	} else {
		fmt.Println(x, "是奇数");
	}
}
/*
go这里没有了break，所以感觉没有以下在何种Ｃ风格的操作
case 1:
	aaa;
case 2:
	bbb;
	break;
case 3:
	ccc;
*/
func TestSwitch(){
	var i int = 5
	switch i{
	case 1:
		fmt.Println("one");
	case 2:
		fmt.Println("two");
	case 3,4,5:
		fmt.Println("other");
	default:
		fmt.Println("end");
	}
}

func TestFor(){
	//way 1
	for i := 1; i < 10; i++{
		fmt.Println(i);
	}

	fmt.Println("----");
	//way 2
	i := 1
	for i < 10 {
		fmt.Println(i);
		i++
	}

	fmt.Println("----");
	//way 3
	i = 1
	for {
		if i == 10{
			break;
		}
		fmt.Println(i);
		i++
	}
}





