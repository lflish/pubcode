from sanic import Sanic
from sanic.response import text

app = Sanic()

@app.route("/")
async def index(request):
    return text('Hello World!')

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8000)
