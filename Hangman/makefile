PROGRAM = hangman
FILES.c = hangman.cpp
FILES.h = hangman.h hgraphics.h
FILES.o = ${FILES.c:.c=.o}

CC = g++
SFLAGS = -std=c++17
GFLAGS = -pg
OFLAGS = -O0
DFLAGS = -I/src
WFLAG1  = -Wall
WFLAG2  = -Wextra
WFLAG3  = -Werror
WFLAG4  = 
WFLAG5  = 
WFLAGS  = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} 
UFLAGS  = # Set on command line only

CFLAGS  = ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS} ${UFLAGS} ${DFLAGS}
LDFLAGS = -lm
LDLIBS  =

all:    ${PROGRAM}

${PROGRAM}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

hangman.o: ${FILES.h}
hgraphics.o: ${FILES.h}

# If it exists, prog1.dSYM is a directory on macOS
DEBRIS = a.out core *~ *.dSYM
RM_FR  = rm -fr

clean:
	${RM_FR} ${FILES.o} ${PROGRAM} ${DEBRIS} 

test:
	${TEST}