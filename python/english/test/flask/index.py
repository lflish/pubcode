# coding:utf-8

from flask import Flask, render_template
from flask import  request
from flask import url_for, redirect
app = Flask(__name__)

word_maps = {}
urls = {}

index = ''

@app.route('/')
@app.route('/index')
def index():

    index = "http://{}".format(request.host)

    for i in range(12):
        urls[i] = "{}/unit/{}" .format(index, i + 1)


    return render_template("base.html", index=index, urls=urls)

@app.route('/unit/<unitno>')
def display(unitno):

    wordlist = {}

    if unitno in word_maps:
        wordlist = word_maps[unitno]
    else:
        wordlist = {}
        word_file = r'static/unit' + unitno + '.dict'
        try:
            for line in open(word_file, 'r', encoding='UTF-8'):
                wordlist[line.split(':')[0]] = line.split(':')[1][0:-1]
        except:
                return "请联系管理员添加Unit%s单元" % unitno

    return render_template("unit.html", index=index, urls=urls, word=wordlist)

if __name__ == '__main__':

    #启动程序
    app.run(host='0.0.0.0', port='80', debug=False)
