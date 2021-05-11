package main

import "fmt"

func FizzBuzz(){
	for i := 1; i <= 100; i++{
		switch {
		case (i % 15) == 0:
			fmt.Println("FizzBuzz")
		case (i % 3) == 0:
			fmt.Println("Fizz")
		case (i % 5) == 0:
			fmt.Println("Buzz")
		default:
			fmt.Println(i)
		}
	}
}

func Sroot(){

}

func UserScanf(){
	for{
		val := 0
		fmt.Print("Enter number: ")
		fmt.Scanf("%d", &val)
		fmt.Println("You Entered:", val)

		switch {
		case val == 0:
			fmt.Println("0 is neither negative nor positive")
		case val < 0:
			panic(" val < 0")
		case val > 0:
			fmt.Printf("You entered: %d\n", val)
		default:
			continue
		}
	}
}

func main() {
	//FizzBuzz()
	UserScanf()
}