package base

/*
包的注意事项：
	对于需要被外部引用的包，第一个字母要大写
	一个文件夹内，只能包含一个包
	被外部调用时，需要带上包名
*/
import "fmt"

func TestHello(){

	fmt.Println("Hello World");

	fmt.Printf("hello world\n")
	fmt.Printf("二进制:%b\n", 255);
	fmt.Printf("八进制:%o\n", 255);
	fmt.Printf("十进制:%d\n", 255);
	fmt.Printf("十六进制:%x\n", 255);
}