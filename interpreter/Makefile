.POSIX:

OBJ=.o
LIB=.a
EXE=
LDOUT=-o
LIBPREFIX=lib
CCNAME=$(CC)
CCOPTS=Makefile.$(CCNAME)

#\
!INCLUDE $(CCOPTS) #\
!IF 0
-include $(CCOPTS) #\
!ENDIF

PROJECT_NAME=karyon
CORE_LIBRARY=$(LIBPREFIX)$(PROJECT_NAME)-core$(LIB)
NATIVE_EXECUTABLE=$(PROJECT_NAME)$(EXE)

all: core native

core: $(CORE_LIBRARY)

$(CORE_LIBRARY): core/Err$(OBJ) core/Log$(OBJ)
	$(AR) $(ARFLAGS) $(AROUT)$@ $?

core/Err$(OBJ): core/Err.c core/Err.h
core/Log$(OBJ): core/Log.c core/Log.h core/Err.h core/std/sys/types.h

native: $(NATIVE_EXECUTABLE)

$(NATIVE_EXECUTABLE): native/Errno$(OBJ) native/Log$(OBJ) native/main$(OBJ) $(CORE_LIBRARY)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $?

native/Errno$(OBJ): native/Errno.c native/Errno.h
native/Log$(OBJ): native/Log.c native/Log.h
