.POSIX:

#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

EXE_DEPS=main$(OBJ) ../core/$(LIBPREFIX)karyon-core$(LIB) ../native/$(LIBPREFIX)karyon$(LIB) $(LIBPREFIX)karyon-javascript$(LIB)
LIB_DEPS=Str$(OBJ) Input$(OBJ) Token$(OBJ)

all: karyon-javascript$(EXE)

karyon-javascript$(EXE): $(EXE_DEPS)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $(EXE_DEPS)

$(LIBPREFIX)karyon-javascript$(LIB): $(LIB_DEPS)
	$(AR) $(ARFLAGS) $(AROUT)$@ $(LIB_DEPS)

# TODO missing deps for main.c? (it'll be removed anyway? plugin to native)
# TODO missing dependencies from core and native headers?
Str$(OBJ): Str.c Str.h
Input$(OBJ): Input.c Input.h
Token$(OBJ): Token.c Token.h Input.h Str.h
