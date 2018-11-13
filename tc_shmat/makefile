target=tc_shmem
target_o=tc_shmem.o
source_c=tc_shmem.c
FLAGS=-wall

$(target):$(target_o)
	cc  -o $(target) $(target_o) $(FLAGS)
$(target_o):$(source_c)
	cc -c $(target_o) $(source_c)
clean:
	rm -f $(target)
	rm -f *.o


