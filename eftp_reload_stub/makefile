TAR=eftp_reload_stub
LIB=
CINCLUDE=
OBJS=db2tc.o

all:TAR

TAR:$(OBJS)
	gcc -o $(TAR) db2tc.o -L $(DB2LIB) -l db2
	db2 bind db2tc.bnd

db2tc.o : db2tc.sqc
	db2 connect to eftp user eftp using eftp
	db2 precompile db2tc.sqc  bindfile
	gcc -I $(DB2_HOME)/include -c -g db2tc.c

clean:
	rm -f *.o *.bnd $(TAR) *.c >/dev/null 2>&1
