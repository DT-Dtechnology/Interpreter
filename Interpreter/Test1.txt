
def deepdiv(i, j):
	while (i % j == 0) :
		i = i / j
		print j
	return i


def is_prime(num):
	j = 2
	flag = True
	while (j * j <= num) :
		if num % j == 0:
			flag = False
			break
		j = j + 1
	if flag:
		print "%d is a prime." % num
		return True
	else:
		print "%d is not a prime." % num
		return False


def main():
	for i in (100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119):
		if is_prime(i):
			continue
		j = 2
		temp = i
		print "%d has factors:" % temp
		while (temp != 1):
			temp = deepdiv(temp, j)
			if temp == 1:
				break
			j = j + 1

main()
