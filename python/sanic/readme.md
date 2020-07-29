## Sanic异步框架学习

### 一、环境搭建
略略略

### 二、Routing
####1.处理函数   
跟Flask类似
```python
from sanic import Sanic
from sanic.response import text

app = Sanic()

@app.route("/")
async def index(request):
    #Flask中直接返回的是字符串，后续文档应该有说明
    return text('Hello World!') 

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8000)
```
example_1

#### 2.请求参数
最简单的调用方式，默认string类型
```python
@app.route('/tag/<tag>')
async def tag_handler(request, tag):
	return text('Tag - {}'.format(tag))
```
可以通过```python:type```来指定类型,支持以下类型
- string   
    “Bob”   
    “Python 3”
- int   
    10  
    -10   
    (No floats work here)
- number   
    1   
    1.5
- alpha   
    “Bob”   
    “Python”   
    (If it contains a symbol or a non alphanumeric character it will fail)
- path   
    “hello”   
    “hello.text”
- uuid    
    123a123a-a12a-1a1a-a1a1-1a12a1a12345 (UUIDv4 Support)
- regex expression   
参考代码如下
```python
from sanic import Sanic
from sanic.response import text

app = Sanic()

@app.route('/string/<string_arg:string>')
async def string_handler(request, string_arg):
    return text('String - {}'.format(string_arg))

@app.route('/int/<integer_arg:int>')
async def integer_handler(request, integer_arg):
    return text('Integer - {}'.format(integer_arg))

@app.route('/number/<number_arg:number>')
async def number_handler(request, number_arg):
    return text('Number - {}'.format(number_arg))

@app.route('/alpha/<alpha_arg:alpha>')
async def number_handler(request, alpha_arg):
    return text('Alpha - {}'.format(alpha_arg))

@app.route('/path/<path_arg:path>')
async def number_handler(request, path_arg):
    return text('Path - {}'.format(path_arg))

@app.route('/uuid/<uuid_arg:uuid>')
async def number_handler(request, uuid_arg):
    return text('Uuid - {}'.format(uuid_arg))
    
if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8000)
```

自动判断类型
```python
@app.route('/int/<integer_arg:int>')
async def integer_handler(request, integer_arg):
    return text('Integer(int) - {}'.format(integer_arg))

@app.route('/int/<integer_arg:string>')
async def integer_handler(request, integer_arg):
    return text('Integer(string) - {}'.format(integer_arg))
```

正则匹配
```python
@app.route('/person/<name:[A-z]+>')
async def person_handler(request, name):
    return text('Person - {}'.format(name))

@app.route('/folder/<folder_id:[A-z0-9]{0,4}>')
async def folder_handler(request, folder_id):
    return text('Folder - {}'.format(folder_id))

```
expmple_2
#### 3.请求类型
```python
#方式一:methods参数
@app.route('/get', methods=['GET'])
async def get_handler(request):
	return text('GET request in default - {}'.format(request.args))
	
#方式二:简洁方式
@app.get('/get')
async def get_handler(request):
	return text('GET request - {}'.format(request.args))
```
example_3

####　４．
