TAR=test
SRCEXT = *.c
GCCFG = gcc
LINKFG = -fPIC -ggdb -Wall -O0 -o 
#SRCFD = . ../tc_test
SRCFD = . ./log
LIB = 
SRC_FILE1 := $(foreach n, $(SRCFD), $(wildcard $(n)/$(SRCEXT))) 
#SRC_FILE := $(foreach n, $(SRCFD)/$(wildcard $(SRCEXT)), $(wildcard $(SRCFD)/$(SRCEXT))) 
#SRC_FILE := $(foreach n, $(SRCFD)/$(wildcard $(SRCEXT)), $(wildcard $(SRCEXT))) 
SRC_FILE := $(foreach n, $(SRCFD), $(wildcard $(n)/$(SRCEXT))) 

#OBJS := $(patsubst %.c, %.o, $(wildcard *.c))
OBJS := $(patsubst %.c, %.o, $(SRC_FILE))
ALLFILE = $(wildcard *.c)
AFFILE =  $(wildcard $(SRCFD)/$(SRCEXT))



SLIBPATH=-L /home/ashen/tc/tc_mk_liba/lib
INC=-I /home/ashen/tc/tc_mk_libso/inc
SLIB=-lprt


$(TAR):$(OBJS)
#	$(GCCFG) $(INC) $(SLIBPATH) $(SLIB) $(LINKFG)  $(TAR) $(OBJS)
	$(GCCFG) $(LINKFG)  $(TAR) $(OBJS) $(INC) $(SLIBPATH) $(SLIB)
$(OBJS):%.o:%.c
	$(GCCFG) $(INC) $(LINKFG) $@  -c $<

#obj:
	#@echo $(SRC_FILE);
	#@echo $(SRCFD)
	#@echo $(OBJS)
.PHONY:clean
clean:
	rm -f $(TAR)
	rm -f *.o


