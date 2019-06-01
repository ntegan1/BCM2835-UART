all: src/main.c
	gcc -g src/main.c -o uart 

edit: 
	vim src/main.c 
	
clean:
	rm -f uart

alias:
	echo 'alias f="make edit && clear && make && sudo ./uart"'
