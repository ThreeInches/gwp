main:main.o
	gcc main.o -o main
main.o:main.s
	gcc -c main.s -o main.o
main.s:main.i
	gcc -S main.i -o main.s
main.i:main.c
	gcc -E main.c -o main.i
.PHONY:clean
Clean:
	rm -f main.i main.s main.o main
