# 微软快餐式学习
### 声明和使用

声明
```go
	var firstName string
	var firstName, lastName string
	var age int
	
	var (
    	firstName, lastName string
    	age int
	)
```
初始化
```go
var (
		firstName string = "John"
		lastName  string = "Doe"
		age       int    = 32
    )

var (
		firstName = "John"
		lastName  = "Doe"
		age       = 32
    )

var (
    firstName, lastName, age = "John", "Doe", 32
)

func main() {
    firstName, lastName := "John", "Doe"
    age := 32
    println(firstName, lastName, age)
}

/* 常量 */
const HTTPStatusOK = 200

const (
    StatusOK              = 0
    StatusConnectionReset = 1
    StatusOtherError      = 2
)
```
注意:定义单不使用，编译可能失败

### 基本数据类型
四种基本类型
基本类型：数字、字符串和布尔值
聚合类型：数组和结构
引用类型：指针、切片、映射、函数和通道
接口类型：接口

```go

/* 整型 */
var integer8 int8 = 127
var integer16 int16 = 32767
var integer32 int32 = 2147483647
var integer64 int64 = 9223372036854775807
println(integer8, integer16, integer32, integer64)

/* 浮点型 */
var float32 float32 = 2147483647
var float64 float64 = 9223372036854775807
println(float32, float64)

/* 字符串 */
var firstName string = "John"
lastName := "Doe"
println(firstName, lastName)

/* 类型转换 */
var integer16 int16 = 127
var integer32 int32 = 32767
println(int32(integer16) + integer32)
```

注意:类型转换必须显式转换
注意:下划线_意味着我们不会使用该变量的值


### 函数

函数创建
```go
func name(parameters) (results) {
    body-content
}

func sum(number1 string, number2 string) int {
    int1, _ := strconv.Atoi(number1)
    int2, _ := strconv.Atoi(number2)
    return int1 + int2
}

/* 可以为返回值设置名字 */
func sum(number1 string, number2 string) (result int) {
    int1, _ := strconv.Atoi(number1)
    int2, _ := strconv.Atoi(number2)
    result = int1 + int2
    return
}
```

返回多个返回值
```go
func calc(number1 string, number2 string) (sum int, mul int) {
    int1, _ := strconv.Atoi(number1)
    int2, _ := strconv.Atoi(number2)
    sum = int1 + int2
    mul = int1 * int2
    return
}

```

更改函数参数值(C中址传递)
```go
package main

func main() {
    firstName := "John"
    updateName(&firstName)
    println(firstName)
}

func updateName(name *string) {
    *name = "David"
}
```

### 包
创建包
如需将某些内容设为专用内容，请以小写字母开始。
如需将某些内容设为公共内容，请以大写字母开始

src/
  calculator/
    sum.go

```go
package calculator

//包内部
var logMessage = "[LOG]"

var Version = "1.0"

//包内部
func internalSum(number int) int {
    return number - 1
}

func Sum(number1, number2 int) int {
    return number1 + number2
}
```

#### 创建模块
包的模块指定了Go运行已组合代码所需的上下文, 此上下文信息包括编写代码时所用的Go版本

```shell
go mod init github.com/myuser/calculator
```
运行此命令后，github.com/myuser/calculator 就会变成包的名称。 在其他程序中，你将使用该名称进行引用。 命令还会创建一个名为 go.mod 的新文件。 最后，树目录现会如下列目录所示：
src/
  calculator/
    go.mod
    sum.go

go.mod内容应该如下
```
module github.com/myuser/calculator
go 1.14
```



