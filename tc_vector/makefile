TAR=stub
SRCEXT = *.c
GCCFG = gcc -fPIC
LINKFG = -ggdb -Wall -O0 -o 
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

$(TAR):$(OBJS)
	$(GCCFG) $(LINKFG)  $(TAR) $(OBJS)
$(OBJS):%.o:%.c
	$(GCCFG) $(LINKFG) $@ -c $<

#obj:
	#@echo $(SRC_FILE);
	#@echo $(SRCFD)
	#@echo $(OBJS)
.PHONY:clean
clean:
	rm -f $(TAR)
	rm -f *.o


