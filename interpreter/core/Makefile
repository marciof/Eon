.POSIX:

OBJ=.o
LIB=.a
LIBPREFIX=lib
CCNAME=$(CC)
CCOPTS=../Makefile.$(CCNAME)

#\
!INCLUDE $(CCOPTS) #\
!IF 0
-include $(CCOPTS) #\
!ENDIF

all: library

library: $(LIBPREFIX)karyon$(LIB)

$(LIBPREFIX)karyon$(LIB): Err$(OBJ) Log$(OBJ)
	$(AR) $(ARFLAGS) $(AROUT)$@ Err$(OBJ) Log$(OBJ)

Err$(OBJ): Err.c Err.h
Log$(OBJ): Log.c Log.h Err.h std/SysTypes.h
