.POSIX:

# Workaround for include-line support on both `make` and `nmake`.
#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

EXT_DEPS=../core/$(LIBPREFIX)karyon-core$(LIB)
EXE_DEPS=main$(OBJ) $(EXT_DEPS) $(LIBPREFIX)karyon-native$(LIB)
LIB_DEPS=Errno$(OBJ) Log$(OBJ)

all: karyon$(EXE)

karyon$(EXE): $(EXE_DEPS)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $(EXE_DEPS)

$(LIBPREFIX)karyon-native$(LIB): $(LIB_DEPS)
	$(AR) $(ARFLAGS) $(AROUT)$@ $(LIB_DEPS)

Errno$(OBJ): Errno.c Errno.h $(EXT_DEPS)
Log$(OBJ): Log.c Log.h Errno.h $(EXT_DEPS)
