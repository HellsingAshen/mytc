TAR=testlua.so
SRCEXT = *.c
GCCFG = gcc 
GCCFLAG = -fPIC -shared -o
LINKFG = 
SRCFD = . 
LIB = 
OUTPUT_LIB = ./lib
SRC_FILE := $(foreach n, $(SRCFD), $(wildcard $(n)/$(SRCEXT))) 


#OBJS := $(patsubst %.c, %.o, $(wildcard *.c))
OBJS := $(patsubst %.c, %.o, $(SRC_FILE))
ALLFILE = $(wildcard *.c)
AFFILE =  $(wildcard $(SRCFD)/$(SRCEXT))

$(TAR):$(OBJS)
	$(GCCFG)  $(OBJS) $(GCCFLAG) $(TAR)
	$(shell mkdir -p ${OUTPUT_LIB})
	mv $(TAR) $(OUTPUT_LIB)
	cp $(OUTPUT_LIB)/*.so .
$(OBJS):%.o:%.c
	#$(GCCFG) $(LINKFG) $@ -c $<
	$(GCCFG) -fPIC -c $(SRC_FILE)

#obj:
	#@echo $(SRC_FILE);
	#@echo $(SRCFD)
	#@echo $(OBJS)
.PHONY:clean
clean:
	rm -f $(TAR)
	rm -f *.o
	rm -fr lib	

