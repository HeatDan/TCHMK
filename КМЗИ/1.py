#!/usr/bin/python
#Шифр Вижинера
import argparse
import sys
 


#Кодирование содержимого
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

if __name__ == "__main__":
    #Парсинг аргументов
    parse = argparse.ArgumentParser()
    parse.add_argument('vhod')
    parse.add_argument('vihod')
    parse.add_argument('key')
    parse.add_argument('mod', choices=['c', 'd'])
    args = parse.parse_args()
    
    #Файл входных данных
try:
    infile = open(args.vhod, 'rb')
except IOError:
    print("Vhodnoi file ne naiden")
    exit (1);
    dannie = infile.read()
    infile.close()

    #Файл с ключом
try:
    keyfile = open(args.key, 'rb')
except IOError:
    print("File kluch ne naiden")
    exit (1);
    key = keyfile.read()
    keyfile.close()


    #Выходной файл
    outfile = open(args.vihod, 'wb')
    mod = (args.mod == 'c')
    process = shifr(dannie, key, mod)
    outfile.write(process)
    outfile.close()