package main

import (
	"fmt"
	"net/http"
	"io/ioutil"
	"io"
	"time"
	"os"
)

func main(){

	ch := make(chan string)
	for _, url := range os.Args[1:]{
		go fetch(url, ch)
	}

	for range os.Args[1:]{
		fmt.Println(<-ch)
	}
}

func fetch(url string, ch chan <- string){
	start := time.Now()

	conn, err := http.Get(url)
	if err != nil {
		fmt.Println("Err:", err)
	}

	byes, err := io.Copy(ioutil.Discard, conn.Body)
	conn.Body.Close()
	if err != nil {
		ch <- fmt.Sprintf("Error:%s %v", url, err)
		return
	}

	sec := time.Since(start).Seconds()
	ch <- fmt.Sprintf("%.2fs %7d %s", sec, byes, url)

	return
}