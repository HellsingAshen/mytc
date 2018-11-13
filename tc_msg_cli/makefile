target=tc_msg_cli
target_o=tc_msg_cli.o
source_c=tc_msg_cli.c
FLAGS=-wall

$(target):$(target_o)
	cc  -o $(target) $(target_o) $(FLAGS)

$(target_o):$(source_c)
	cc -c $(target_o) $(source_c) $(FLLAGS)

clean:
	rm -f $(target)
	rm -f *.o


