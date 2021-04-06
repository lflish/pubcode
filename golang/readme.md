# Go语言学习笔记
## 第一章 

## 第二章

### 2.1 名称
**关键字**  

    break default func interface select 
    case defer go map struct
    chan else goto package switch
    const fallthrough if range type
    continue for import return var

预声明

**常量**:	

	true false iota nil

**类型**:

	int,int8,int16,int32,int64
	uint,uint8,uint16,uint32,uint64,uintptr
	float32,float64,complex128,complex64
	bool,byte,rune,string,error
**函数**:
	
	make,len,cap,new,append,copy,close,delete
	complex,real,imag,panic,recover

**注:go程序员一般使用 驼峰式的风格,而不是linux中小写下划线组合**

### 2.2声明
变量(var)
常量(const)
类型(type)
函数(func)

```go
package main /* 开头是package声明，表明文件属于哪个包*/
import "fmt"	/* 然后是引用声明 */
```
变量声明
```go
var name type = expression /* 创建变量 */
/* eg */
var i, j, k int /* int int int */
var b, f, s = true, 2.3, "four" /* bool, float64, string */


### 2.3变量

```
短变量声明,类型由expression决定
```go
name := expression

/* eg */
t := 0.0
i := 100
i,j := 0, 1
```
**注: := 表示声明, =表示赋值**

指针
```go
	x := 1
	p := &x
	fmt.Println(*p);
	*p = 2
	fmt.Println(x)
```

new
```go
	p := new(int) /* *int 类型的p */
	*p = 2
	fmt.Println(*p)
```

### 2.4赋值

```go
	x = 1
	*p = true
	v : 1
	v++
```
多重赋值

```go
	x, y = y, x
	a[i], a[j] = a[j], a[i]

	/* 不需要的值赋值给_空标识符 */
	_, err = io.Copy(dst, src)/* 丢弃字节个数*/
```
赋值规则:类型必须精确匹配, nil可以被赋给任何接口变量或者引用类型

### 2.5类型声明
	type name underlying-type
类型声明通常 出现在包级别，类似于c中的typedef, 如果名字是导出的开头使用大写字母
```go
	type uint64_t uint64
```

### 2.6 包和文件
一个包的源代码保存在一个或多个以.go结尾的文件中，它所在目录名的尾部就是包的导入路径，
同一个包中，在一个文件声明的变量，在包的其他文件中是可见的
每一个包给他的申明提供了独立的命名空间,使用时必须指明所指的是哪个
```go
	/* eg */
	image.Decode()
	utf16.Decode()
```
package声明前紧挨着的文档注释是对整个包进行描述
扩展的文档注释通常放在一个doc.go的文件中

导入
```go
	/*1*/
	import(
		"fmt"
		"os"
	)
	/*2*/
	import "fmt"
```
如果导入一个没被引用的包，会触发一个错误
导入声明可以给导入的包绑定一个短名字，用来在整个文件中引用包的内容

包初始化

包的初始化从初始化包级别的变量开始，这些变量按照声明顺序初始化
任何文件可以包含任意数量的init函数，这个init函数不能被调用和被引用

### 2.7 作用域

声明的作用域是申明在程序文本中出现的区域，它是一个编译属性，
变量的生命周期是变量在执行期间能被程序的其他部分引用的起止时间，他是一个运行时属性

## 第三章 基本数据结构

Go数据类型四大分类: 基础类型，聚合类型，引用类型和接口类型

### 3.1 整数
rune类型是int32同义词,常用语指明Unicode码点
uintptr无符号整数，大小不确定但是足够房完整的指针

取模余数的正负号总是与被除数一致

一元运算符
+ 一元取正
- 一元取负

& 位运算and
| 位运算or
^ 位运算xor
&^ 位清空
<< 左移
>> 右移

通常将某种类型的值换换位另一种需要显式转换

```go
	var apples int32 = 1
	var oranges int16 = 2
	var compote int = apples + oranges /* 编译错误 */
```

类型转换
```go
	var compote = int(apples) + int(oranges)
	/*缩减整数大小，以及整型预付电信转换可能改变值或者损失精度*/
	f := 3.141
	i := int(f) /* i=3 */
	f = 1.99
	int(f) 	/*1*/

	f := 1e100
	i := int(f) /*结果依赖实现*/

```
注意:fmt的两个技巧，通常Printf的格式化字符串含有多个%符号,这就要提供多个操作数，
	而%后的符号是[1]告知Printf重复使用第一个操作数
	其次，%o,%x或者%X之前的#告知Printf输出相应的前缀

```go
	o := 0666
	fmt.Printf("%d %[1]o %#[1]o\n", o)/* 438 666 0666*/
```

文字符号
ascii := 'a'
unicode := '国'
newline := '\n'

fmt.Printf("%d %[1]c, %[1]q", ascii);
fmt.Printf("%d %[1]c, %[1]q", unicode);
fmt.Printf("%d %[1]c, %[1]q", newline);

### 3.2 浮点数
Go具有两种大小的浮点数，float32和float64

math给出了浮点值的极限 math.MaxFloat32是float32的最大值
math.MaxFloat64是float64的最大值


# Base目录 原先学习记录 








