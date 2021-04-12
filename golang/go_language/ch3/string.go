package ch3

import (
	"bytes"
	"fmt"
)
import "unicode/utf8"

func Ch3StrTest1() {
	s := "Hello World"
	u := "你好啊，世界唧唧"

	fmt.Printf("%s:[%c]\n", s, s[6])
	fmt.Printf("%s:[%c]\n", u, u[6])
}
func Ch3StrTest2() {
	a := "世界"
	b := "\xe4\xb8\x96\xe7\x95\x8c"
	c := "\u4e16\u754c"
	d := "\U00004e16\U0000754c"

	fmt.Printf("a:%s\n", a)
	fmt.Printf("b:%s\n", b)
	fmt.Printf("c:%s\n", c)
	fmt.Printf("d:%s\n", d)
}

func Ch3StrTest3() {
	s := "Hello, 世界"

	fmt.Println(len(s))
	fmt.Println(utf8.RuneCountInString(s))

	for i := 0; i < len(s); {
		r, size := utf8.DecodeRuneInString(s[i:])
		fmt.Printf("%d\t%c\n", i, r)
		i += size
	}
}

/* int to string*/
/* 追加utf-8字符最好使用WriteRune */
/* 追加ascii字符最好使用 WriteByte */
func Ch3StrTest4(values []int) string {
	var buf bytes.Buffer
	buf.WriteByte('[')
	for i, v := range values {
		if i > 0 {
			buf.WriteString(", ")
		}
		fmt.Fprintf(&buf, "%d", v)
	}
	buf.WriteByte(']')

	return buf.String()
}
