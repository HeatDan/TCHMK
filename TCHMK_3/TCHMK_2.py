#!/usr/bin/python
import longNumber
import sys


def printUsage():
	print "Usage: "
	print "TCHMK_1 <A filelame> <operation> <B filelame> <resultult filename> [-b] [<modul filename>]"
	print "Parameters:"
	print "  operations:"
	print "    \"+\" - addition"
	print "    \"-\" - subtraction"
	print "    \"*\" - multiplication"
	print "    \"/\" - division"
	print "    \"%\" - taking the remainder"
	print "    \"^\" - involution (pow)"
	print "  -b for operations with binary files"


def process(A, B, modul, operation):
	zero = longNumber.longNumber("0")
	resultult = zero

	if (modul < zero):
		print "Negative modul!"
		return False, resultult

	if operation == '^':
		resultult = longNumber.Pow(A, B, modul)
		return True, resultult

	if (modul > zero):
		A = A % modul
		B = B % modul

	if operation == '+':
		resultult = A + B

	elif operation == '-':
		resultult = A - B

	elif operation == '*':
		resultult = A * B

	elif operation == '/':
		if B == zero:
			print "Division by zero"
			return False, resultult
		resultult = A / B

	elif operation == '%':
		if (B == zero):
			print "Division by zero"
			return False, resultult
		resultult = A % B

	if (modul > zero):
			resultult = resultult % modul
			while (resultult < zero):
				resultult = resultult + modul

	return True, resultult


def main():
	if len(sys.argv) < 5:
		print "Too few arguments passed."
		printUsage()
		return -1

	if len(sys.argv) > 7:
		print "Too many arguments passed."
		printUsage()
		return -1
	
	fileA = sys.argv[1]
	operation = sys.argv[2]
	fileB = sys.argv[3]
	fileresult = sys.argv[4]
	binary = False
	fileMod = None

	if len(sys.argv) == 6:
		if sys.argv[5] == "-b":
			binary = True
		else:
			fileMod = sys.argv[5]

	if len(sys.argv) == 7:
		binary = True;
		fileMod = sys.argv[6]
	
	A = longNumber.longNumber(0)
	B = longNumber.longNumber(0)
	modul = longNumber.longNumber(0)
	
	if binary == True:
		A.ReadBinFile(fileA)
		B.ReadBinFile(fileB)
		if fileMod != None:
			modul.ReadBinFile(fileMod)
	else:
		A.ReadFile(fileA)
		B.ReadFile(fileB)
		if fileMod != None:
			modul.ReadFile(fileMod)
	
	isProcess, resultult = process(A, B, modul, operation)
	if not isProcess:
		sys.exit(-1)
		
	if binary == True:
		resultult.SaveBinFile(fileresult)
	else:
		resultult.SaveNumberToFile(fileresult)
			

if __name__ == "__main__":
	main()