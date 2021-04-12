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
```

### 2.3变量

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
```go
+ 一元取正
- 一元取负

& 位运算and
| 位运算or
^ 位运算xor
&^ 位清空
<< 左移
>> 右移
```

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

%g: 会自动保持足够的精度  
%e: 指数输出  
%f: 无指数输出  

```go
 for x := 0; x < 8; x++{
 	fmt.Printf("x=%d,e = %8.3f\n", x, match.Exp(float64(x)))
}
 
var z float64

/* NaN表示无意义的运算结果 */
fmt.Printf(z, -z, -1/z, z/z) /* 0 -0 +Inf, -Inf, NaN*/

/* 不可直接与NaN进行比较 */
nan := math.NaN()
fmt.Println(nan == nan, nan < nan, nan > nan) /* false */

/* 一个函数的返回值是浮点型的话，最好单独报错 */
func compute()(value float64, ok bool){
	if failed{
		return 0, false
	}
	return result, true
}
```

### 3.3 复数
略

### 3.4 布尔值
遵循c语言中的短路行为, 其中 && 优先级高于 ||
```go
if 'a' <= c && c <= 'z' ||
	'A' <= c && c <= 'Z' ||
	'0' <= c && c <= '9'{
	/* ascii 或者数字 */
}
```
布尔值无法隐式转换为整型,可以写个转换函数进行转换

### 3.5 字符串
内置函数len返回字符串的字节数，下表访问s[i]获取第i个字符
字符串的第i个字节不一定就是第i个字符,因为非ascii字符的utf-8需要两个或者多个字节   

子串: s[i:j]生成一个新的字符串,i,j默认为0和len(s)

注:如果下标越界或者j小于i值，会触发崩溃

加号 + 链接两个字符串生成新的字符串

字符串支持比较运算符，== 和 <;按字节进行比较

```go

s := "left foot"
t := s
s += ", right foot"
/* 以上并不改变s原有的值,字符串的值不可改变，内部数据不可修改 */
s[0] = 'L' /* 编译报错,s[0]无法赋值 */
```

#### 转义字符
```go
\a
\b
\f 换页
\n 换行
\r 回车
\t 制表符
\v
\'
\"
\\
\xhh 十六进制
\000 八进制
```
#### 原生字符串常量值
使用反引号`....`,原生的字符串字面量内，转义序列不起作用，实质内容与字面写法完全一致
包括反斜杠和换行符(回车会被删除)

#### unicode
unicode包含了所有文书体系的字符
在go中，这些字符记号称为文字符号(rune),实质是int32的别名

#### UTF-8
以字节为单位，对unicode做变长编码,每个字符用1～4个字节来表示
```go
// 对编码的转义
\uhhhh
\Uhhhhhhhh

"世界"
"\xe4\xb8\x96\xe7\x95\x8c"
"\u4e16\u754c"
"\U00004e16\U0000754c"

```
```go
import "unicode/utf8"
s := "Hello, 世界"
fmt.Println(len(s)) // "13"
fmt.Println(utf8.RuneCountInString(s)) // "9"
```

当[]rune转换用于utf-8编码字符串是，返回盖字符串的unicode序列
```go
s := "中国"
fmt.Printf("% x\n", s) /* %与x中间有空格 */

r := []rune(s)
fmt.Printf("%x\n", r)
```

如果将一个整数转换为字符串，其值按文字符号类型解读
```go
fmt.Println(string(65)) //打印A而不是65
```

#### 字符串和字节slice
常用四个标字符串包:bytes，strings，strconv，unicode
strings: 提供了许多函数，搜索，替换切片等
bytes: 功能与上类似,用于操作字节slice
strconv: 主要用于转换布尔,整数，浮点数，或者字符串转换为整型，浮点等
unicode: 判别文字符号特性,IsDigit，IsLetter等

常用预备函数
```go
/* string包 */
func Contains(s, substr string)bool;
func Count(s, sep string)int;
func Fields(s string)[]string;
func HasPrefix(s, prefix string)bool;
func Index(s, sep string)int;
func Join(a []string, sep string)string;

/* bytes包 */
func Contains(b, subslice []byte) bool;
func Count(s, sep []byte) int;
func Fields(s []byte) [][]byte;
func HasPrefix(s, prefix []byte) bool;
func Index(s, sep []byte) int
func Join(s [][]byte, sep []byte) []byte
```
bytes包为高效处理字节slice提供了Buffer类型
参考Ch3StrTest4

#### 字符串和数字的相互转换
把整型转换为字符串: fmt.Sprintf或者strconv.Itoa()
```go
x := 123
y := fmt.Sprintf("%d", x)

//FormatInt,FormatUint可以按不同的进制格式化数字
fmt.Println(strconv.FormatInt(int64(x), 2)) // "1111011"
// 或者
s := fmt.Sprintf("x=%b", x) //"1111011"

/* 字符串转换整型 */
x, err := strconv.Atoi("123")

/* ParseInt 用于解释表示整数的字符串 */
y, err := strconv.ParseInt("123", 10, 64)
```



### 3.6 常量

常量的声明,如果没有显示指定类型，那么根据右边表达式推断
```go
const pi = 3.1415926
//或者
const (
	e = 2.71818	
	pi = 3.141592
)

const (
	a = 1
	b
	c = 2
	d
)
fmt.Println(a, b, c, d) /* 1 1 2 2 */
```

对于常量操作数,所有数学运算，逻辑运算和比较运算的结果依然是常量

#### 常量生成器 iota
iota可以创建一系列相关值
```go
type Weekday int
const (
	Sunday Weekday = iota
	Monday
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
)
//以上分别从0开始，以此类推

//net包部分用例
type Flags uint
const (
	FlagUp Flags = 1 << iota
	FlagBroadcast
	FlagLoopback
	FlagPointToPoint
	FlagMulticast
)
```
#### 无类型常量
编译器将从属类型待定的常量表示成某些值,这些值比基本类型的数字精度更高
在将无类型常量转化为接口值时，默认类型分外重要，他们决定了值得动态类型
```go
fmt.Printf("%T\n", 0) 	//int
fmt.Printf("%T\n", 0.0)//float64
fmt.Printf("%T\n", 0i)//complex128
fmt.Printf("%T\n", '\000')//int32
```

# 微软快餐式学习
声明
```go
```
var firstName string


# Base目录 原先学习记录 








