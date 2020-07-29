from sanic import Sanic
from sanic.response import text

app = Sanic()

@app.route('/string/<string_arg:string>')
async def string_handler(request, string_arg):
    return text('String - {}'.format(string_arg))


@app.route('/int/<integer_arg:int>')
async def integer_handler(request, integer_arg):
    return text('Integer(int) - {}'.format(integer_arg))

@app.route('/int/<integer_arg:string>')
async def integer_handler(request, integer_arg):
    return text('Integer(string) - {}'.format(integer_arg))


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


@app.route('/person/<name:[A-z]+>')
async def person_handler(request, name):
    return text('Person - {}'.format(name))


@app.route('/folder/<folder_id:[A-z0-9]{0,4}>')
async def folder_handler(request, folder_id):
    return text('Folder - {}'.format(folder_id))

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8000)
