package main

import (
	"fmt"
	"net/http"
	"io/ioutil"
	"os"
)

func main(){
	for _, url := range os.Args[1:]{

		conn, err := http.Get(url)
		if err != nil {
			fmt.Println("Err:", err)
			continue
		}

		data, err := ioutil.ReadAll(conn.Body)
		conn.Body.Close()
		if err != nil {
			fmt.Println("ReadErr:", err)
			continue
		}

		fmt.Printf("%s", data)
	}
}
