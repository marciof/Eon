.POSIX:

#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

all: karyon-js$(EXE)

karyon-js$(EXE): main$(OBJ) ../core/$(LIBPREFIX)karyon-core$(LIB) ../native/$(LIBPREFIX)karyon$(LIB) $(LIBPREFIX)karyon-js$(LIB)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $?

$(LIBPREFIX)karyon-js$(LIB): Str$(OBJ) Input$(OBJ) Token$(OBJ)
	$(AR) $(ARFLAGS) $(AROUT)$@ $?

# TODO missing dependencies for main.c? (it'll be removed anyway?)
# TODO missing dependencies from core and native headers?
Str$(OBJ): Str.c Str.h
Input$(OBJ): Input.c Input.h
Token$(OBJ): Token.c Token.h Input.h Str.h
