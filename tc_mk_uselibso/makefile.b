TAR=test
SRCEXT = *.c
GCC= gcc
GCCFG = -fPIC
LINKFG = -ggdb -Wall 
#SRCFD = . ../tc_test
SRCFD = . 

DYLIBPATH=-L /home/ashen/tc/tc_mk_libso/lib
INC=-I /home/ashen/tc/tc_mk_libso/inc
DYLIB=-lprt
SRC_FILE := $(foreach n, $(SRCFD), $(wildcard $(n)/$(SRCEXT))) 
OBJS := $(patsubst %.c, %.o, $(SRC_FILE))

#all: $(OBJS) $(TAR)
	
#$(TAR):$(OBJS)
#	$(GCC) $(GCCFG) $(LINKFG) $(OBJS) $(INC) $(DYLIBPATH) $(DYLIB) -o $(TAR)
$(OBJS):%.o:%.c
	@echo  hello
	@echo  ----$@
#	$(GCC) $(INC) $(GCCFG) $(LINKFG) $@ -c $<
	$(GCC)  $(GCCFG)  $(LINKFG) $@  -c $<


obj:
	@echo $(OBJS)
.PHONY:clean
clean:
	rm -f $(TAR)
	rm -f *.o


