.POSIX:

#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

EXE_DEPS=main$(OBJ) ../core/$(LIBPREFIX)karyon-core$(LIB) $(LIBPREFIX)karyon-native$(LIB)
LIB_DEPS=Errno$(OBJ) Log$(OBJ)

all: karyon$(EXE)

karyon$(EXE): $(EXE_DEPS)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $(EXE_DEPS)

$(LIBPREFIX)karyon-native$(LIB): $(LIB_DEPS)
	$(AR) $(ARFLAGS) $(AROUT)$@ $(LIB_DEPS)

# TODO missing dependencies for main.c?
# TODO missing dependencies from core headers?
Errno$(OBJ): Errno.c Errno.h
Log$(OBJ): Log.c Log.h Errno.h
