.POSIX:

# Workaround for include-line support on both `make` and `nmake`.
#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

LIB_DEPS=Err$(OBJ) Log$(OBJ)

all: $(LIBPREFIX)karyon-core$(LIB)

$(LIBPREFIX)karyon-core$(LIB): $(LIB_DEPS)
	$(AR) $(ARFLAGS) $(AROUT)$@ $(LIB_DEPS)

Err$(OBJ): Err.c Err.h
Log$(OBJ): Log.c Log.h Err.h std/sys/types.h
