from sanic import Sanic
from sanic.response import text

app = Sanic()

#方式一
@app.route("/get1/")
async def index(request):
    #return text('get1:[%ｓ]\n' % request.args)
    return text('GET request - {}'.format(request.args))

@app.route("/post1/", methods=['POST'])
async def index(request):
    return text('post1:[%ｓ]\n' % request.args)

#方式二
@app.get("/get2")
async def index(request):
    return text('get2:[%ｓ]\n' % type(request.args))

@app.post("/post2/")
async def index(request):
    return text('post2:[%ｓ]\n' % request.args)


if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8000)
