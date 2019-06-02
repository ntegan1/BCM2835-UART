all:
	gcc src/uart.c src/sbus.c src/sbus.h src/a.c -o a.out
alias:
	echo 'alias f="make edit && clear && make && sudo ./a.out"'
edit:
	vim src/sbus.c src/sbus.h src/a.c
