.POSIX:

#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

all: karyon$(EXE)

karyon$(EXE): Errno$(OBJ) Log$(OBJ) main$(OBJ) ../core/$(LIBPREFIX)karyon$(LIB)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $?

Errno$(OBJ): Errno.c Errno.h
Log$(OBJ): Log.c Log.h
