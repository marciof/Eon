.POSIX:

SRC=.
CCDEFAULTS=$(SRC)/../Makefile.$(CC)

#\
!INCLUDE $(CCDEFAULTS) #\
!IF 0
-include $(CCDEFAULTS) #\
!ENDIF

all: $(LIBPREFIX)karyon$(LIB)

$(LIBPREFIX)karyon$(LIB): Err$(OBJ) Log$(OBJ)
	$(AR) $(ARFLAGS) $(AROUT)$@ Err$(OBJ) Log$(OBJ)

Log$(OBJ): $(SRC)/Err.h
