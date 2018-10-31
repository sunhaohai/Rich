rich: init.o display.o rich.o run.o
	gcc init.o display.o rich.o run.o -o rich
init.o: init.c
	gcc -c init.c
display.o: display.c
	gcc -c display.c
rich.o: rich.c
	gcc -c rich.c
run.o: run.c
	gcc -c run.c
clean:
	rm *.o rich

