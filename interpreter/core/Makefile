.POSIX:

SRC=.
CCNAME=$(CC)
CCOPTS=$(SRC)/../Makefile.$(CCNAME)

#\
!INCLUDE $(CCOPTS) #\
!IF 0
include $(CCOPTS) #\
!ENDIF

all: $(LIBPREFIX)karyon$(LIB)

$(LIBPREFIX)karyon$(LIB): Err$(OBJ) Log$(OBJ)
	$(AR) $(ARFLAGS) $(AROUT)$@ Err$(OBJ) Log$(OBJ)

Log$(OBJ): $(SRC)/Err.h
