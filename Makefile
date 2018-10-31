rich: init.o display.o rich.o run.o 
	gcc init.o display.o rich.o run.o -o rich

test: init.o display.o  run.o test.o
	gcc init.o display.o  run.o test.o -o test

init.o: init.c
	gcc -c init.c
display.o: display.c
	gcc -c display.c
rich.o: rich.c
	gcc -c rich.c
run.o: run.c
	gcc -c run.c
test.o: test.c 
	gcc -c test.c
clean:
	rm *.o rich test

