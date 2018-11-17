target=tc_msg_srv
target_o=tc_msg_srv.o
source_c=tc_msg_srv.c
FLAGS=-wall

$(target):$(target_o)
	cc  -o $(target) $(target_o) $(FLAGS)
$(target_o):$(source_c)
	cc -c $(target_o) $(source_c)
clean:
	rm -f $(target)
	rm -f *.o


