# -*- coding: utf-8 -*-
#/bin/python3
'''
根据参数下载单词的解释
单个:
批量:
'''
import sys
import uuid
import requests
import hashlib
import time
import json
import getopt

reload(sys)
sys.setdefaultencoding('utf-8')

YOUDAO_URL = 'http://openapi.youdao.com/api'
APP_KEY = '6725648272c08031'
APP_SECRET = 'ED91eAzjkUorqE0ol2grTb9oTkXRmgfi'


def encrypt(signStr):
	hash_algorithm = hashlib.sha256()
	hash_algorithm.update(signStr.encode('utf-8'))
	return hash_algorithm.hexdigest()


def truncate(q):
	if q is None:
		return None
	size = len(q)
	return q if size <= 20 else q[0:10] + str(size) + q[size - 10:size]


def do_request(data):
	headers = {'Content-Type': 'application/x-www-form-urlencoded'}
	return requests.post(YOUDAO_URL, data=data, headers=headers)

def connect(out, q = "hello"):
	data = {}
	data['from'] = 'EN'
	data['to'] = 'zh-CHS'
	data['signType'] = 'v3'
	curtime = str(int(time.time()))
	data['curtime'] = curtime
	salt = str(uuid.uuid1())
	signStr = APP_KEY + truncate(q) + salt + curtime + APP_SECRET
	sign = encrypt(signStr)
	data['appKey'] = APP_KEY
	data['q'] = q
	data['salt'] = salt
	data['sign'] = sign

	response = do_request(data)
	out.write(response.content + '\n')

def usage():
	print("\n使用方法:")
	print("\tpython download.py [test]|[-f unit1.txt] [-o recv.txt]\n")
	print("\teg:python download.py test")
	print("\teg:python download.py -f unit1.txt\n")

def main():

	fileout = 'word.txt'	
	filein	= ''

	opts, args = getopt.getopt(sys.argv[1:], "hf:o:")
	for (key,value) in opts:
		if key == '-h':
			usage()
			return 0

		elif key == '-o':
			fileout = value

		elif key == '-f':
			filein = value

	fd_out = open(fileout, 'w')

	if filein != '':
		for line in open(filein, 'r'):
			word = line[0:-1]
			connect(fd_out, word)

	for word in args:
		connect(fd_out, word)

	fd_out.close()

if __name__ == '__main__':
	main()

