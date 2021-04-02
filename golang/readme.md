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
每一个包给他的申明提供了独立的命名空间,使用时必须指明所指的是哪个
同一个包中，在一个文件声明的变量，在包的其他文件中是可见的
```go
	/* eg */
	image.Decode()
	utf16.Decode()
```
package声明前紧挨着的文档注释是对整个包进行描述
扩展的文档注释通常放在一个doc.go的文件中

导入
如果导入一个没被引用的包，会触发一个错误
导入声明可以给导入的包绑定一个短名字，用来在整个文件中引用包的内容





# Base目录 原先学习记录 
