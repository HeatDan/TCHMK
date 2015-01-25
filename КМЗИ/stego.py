#!/usr/bin/env python
# coding: UTF-8

import argparse
from PIL import Image

def hideByte(pix, i, byte):
    for j in range(8):
        pix[i + j] &= 0b11111110 | byte & 1
        byte >>= 1
    

def extractByte(pix, i):
    byte = 0
    for j in range(8):
        byte |= (pix[i + j] & 1) << j
    return byte


def lsb_in(picture, dannie):
    if len(dannie) > 255:
        return None
    try:
    	pic = Image.open(picture)
    except Exception as err:
	print ("Error: {0}".format(err))
	return
    pixString = pic.tobytes()
    pix = [ord(x) for x in pixString]

    dannie = [len(dannie)] + [ord(x) for x in dannie]

    for i, byte in enumerate(dannie):
        hideByte(pix, i * 8, byte)

    pixString = ''.join([chr(x) for x in pix])
    pic.frombytes(pixString)
    reName = picture[:-4] + 'code' + '.bmp'
    pic.save(reName, "BMP")
    return reName


def lsb_out(picture):
    pic = Image.open(picture)
    pixString = pic.tobytes()
    pix = [ord(x) for x in pixString]

    size = extractByte(pix, 0)
    dannie = [0] * size
    for i in range(size):
        dannie[i] = extractByte(pix, (i+1) * 8)

    result = [chr(x) for x in dannie]
    return ''.join(result)
    
def readfile(path):
     with open(path, 'rb') as g:
	dannie = g.read()
    	return dannie

def main():
    parse = argparse.ArgumentParser()
    parse.add_argument('picture')
    parse.add_argument('-i', '--vhod_dannie', nargs='?', help="File with dannie for hiding")
    parse.add_argument('-o', '--vihod_dannie', nargs='?', help="File for extracted dannie")
    args = parse.parse_args()

    if args.vhod_dannie:
    	try:
        	dannie = readfile(args.vhod_dannie)
    	except Exception as err:
        	print("Error: {0}".format(err))
        	return

        if not lsb_in(args.picture, dannie):
            print "Can't hide this file to this picture"
    elif args.vihod_dannie:
        extracted = lsb_out(args.picture)

        outfile = open(args.vihod_dannie, 'wb')
        outfile.write(extracted)
        outfile.close()
    else:
        print "specify vhod_dannie for hiding or vihod_dannie for extracting"

if __name__ == "__main__":
	main()
