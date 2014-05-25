rshellmake: rshell.c tokenize.c redirect.c piping.c
	gcc -Wall -o rshell rshell.c tokenize.c redirect.c piping.c
	./rshell