#!/usr/bin/python
#���� ��������
import argparse
import sys
 
def readfile(path):
    #���� ������� ������
     with open(path, 'rb') as g:
	dannie = g.read()
    	return dannie

def readkey(path):
    #���� � ������
    with open(path, 'rb') as d:
     key = d.read()
     return key

#����������� �����������
def shifr(dannie, key, proc):
    process = str()
    for i in range(len(dannie)):
        a = ord(dannie[i])
        b = ord(key[i % len(key)])
        if proc:
            c = (a + b) % 256
        else:
            c = (a - b + 256) % 256
        process += chr(c)
    return process

def main():
    #������� ����������
    parse = argparse.ArgumentParser()
    parse.add_argument('vhod')
    parse.add_argument('vihod')
    parse.add_argument('key')
    parse.add_argument('mod', choices=['c', 'd'])
    args = parse.parse_args()
    
    try:
        dannie = readfile(args.vhod)
    except Exception as err:
        print("Error: {0}".format(err))
        return
    try:
    	  key = readkey(args.key)
    except Exception as err:
        print("Error: {0}".format(err))
        return



    #�������� ����
    outfile = open(args.vihod, 'wb')
    mod = (args.mod == 'c')
    process = shifr(dannie, key, mod)
    outfile.write(process)
    outfile.close()

if __name__ == "__main__": 
    main()