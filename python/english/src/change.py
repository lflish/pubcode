# -*- coding: utf-8 -*-
#/bin/python3

import os
import json
import sys

def test():
	for line in open('word.txt', 'r'):
		dic = json.loads(line[0:-1])
		print(json.dumps(dic, indent = 4, ensure_ascii = False))

def error():
	print('errorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n')

def main():
	files = sys.argv[1]
	for line in open(files, 'r'):
		dic = json.loads(line[0:-1])
		key = dic['query']

		if key == '':
			error()

		if 'basic' in dic:
			value = dic['basic']['explains'][0]
		else:
			value = dic['translation'][0]

		print('{%s:%s}' % (key, value))

if __name__ ==  '__main__':
	main()


