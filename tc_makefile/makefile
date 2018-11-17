target=tc_01
target_o=tc_thread_01.o
target_c=tc_thread_01.c
FLAGS=-wall  -lpthread

$(target):$(target_o)
	cc  -o $(target) $(target_o) $(FLAGS)
$(target_o):$(target_c)
	cc -c $(target) $(target_c)
clean:
	rm -f $target
	rm -f *.o


