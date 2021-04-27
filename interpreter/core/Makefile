.POSIX:

#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

all: $(LIBPREFIX)karyon-core$(LIB)

$(LIBPREFIX)karyon-core$(LIB): Err$(OBJ) Log$(OBJ)
	$(AR) $(ARFLAGS) $(AROUT)$@ $?

Err$(OBJ): Err.c Err.h
Log$(OBJ): Log.c Log.h Err.h std/sys/types.h
