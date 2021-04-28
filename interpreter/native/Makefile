.POSIX:

#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

all: karyon$(EXE)

karyon$(EXE): main$(OBJ) ../core/$(LIBPREFIX)karyon-core$(LIB) $(LIBPREFIX)karyon$(LIB)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $?

$(LIBPREFIX)karyon$(LIB): Errno$(OBJ) Log$(OBJ)
	$(AR) $(ARFLAGS) $(AROUT)$@ $?

# TODO missing dependencies for main.c?
# TODO missing dependencies from core headers?
Errno$(OBJ): Errno.c Errno.h
Log$(OBJ): Log.c Log.h
