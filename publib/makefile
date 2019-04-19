TAR=libpubc.a
SRCEXT = *.c
GCCFG = gcc 
LINKFG = 
SRCFD = . 
LIB = 
OUTPUT_LIB = ./lib
AR = ar rc 
SRC_FILE := $(foreach n, $(SRCFD), $(wildcard $(n)/$(SRCEXT))) 


#OBJS := $(patsubst %.c, %.o, $(wildcard *.c))
OBJS := $(patsubst %.c, %.o, $(SRC_FILE))
ALLFILE = $(wildcard *.c)
AFFILE =  $(wildcard $(SRCFD)/$(SRCEXT))

$(TAR):$(OBJS)
	$(AR)  $(TAR) $(OBJS)
	$(shell mkdir -p ${OUTPUT_LIB})
	mv $(TAR) $(OUTPUT_LIB)
$(OBJS):%.o:%.c
	#$(GCCFG) $(LINKFG) $@ -c $<
	$(GCCFG) -c  $(SRC_FILE)

#obj:
	#@echo $(SRC_FILE);
	#@echo $(SRCFD)
	#@echo $(OBJS)
.PHONY:clean
clean:
	rm -f $(TAR)
	rm -f *.o
	rm -fr lib/$(TAR)

