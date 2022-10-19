SRCDIR = ../src
INCLUDEDIR = ../include
OBJDIR = ../obj
BINDIR = ../bin


INCLUDEFLAGS = -I${INCLUDEDIR}
CFLAGS = -c -g  -Wall -lpthread ${INCLUDEFLAGS}
PROFILEFLAGS = -pg

profile:
	gcc ${PROFILEFLAGS} ${CFLAGS} ${SRCDIR}/client.c -o ${OBJDIR}/client.o
	gcc ${PROFILEFLAGS} ${OBJDIR}/client.o -o ${BINDIR}/client 
	
	gcc ${PROFILEFLAGS} ${CFLAGS} ${SRCDIR}/server.c -o ${OBJDIR}/server.o
	gcc ${PROFILEFLAGS} ${OBJDIR}/server.o -o ${BINDIR}/server 
	
all:
	gcc  ${CFLAGS} ${SRCDIR}/client.c -o ${OBJDIR}/client.o
	gcc  ${OBJDIR}/client.o -o ${BINDIR}/client 
	
	gcc  ${CFLAGS} ${SRCDIR}/server.c -o ${OBJDIR}/server.o
	gcc  ${OBJDIR}/server.o -o ${BINDIR}/server 

copy:
	cp ${SRCDIR}/server.c ${SRCDIR}/server-a.c
