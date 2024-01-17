default:
	@gcc -Wall -std=c11 -pedantic main.c pigeon.c -o main
	@./main
