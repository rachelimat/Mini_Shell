all: mini_shell.c
	gcc mini_shell.c -o mini_shell
all-GDB: mini_shell.c
	gcc -g mini_shell.c -o mini_shell