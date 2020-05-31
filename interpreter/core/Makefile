.POSIX:

SRC=.
OUT=.
CCDEFAULTS=$(SRC)/../Makefile.$(CC)
LIBPREFIX=lib
LIBSUFFIX=.a

all: $(OUT)/$(LIBPREFIX)karyon$(LIBSUFFIX)

$(OUT)/$(LIBPREFIX)karyon$(LIBSUFFIX): $(OUT)/Err.o $(OUT)/Log.o
	$(AR) $(ARFLAGS) $@ $(OUT)/Err.o $(OUT)/Log.o

$(OUT)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/Log.o: $(SRC)/Err.h

#\
!INCLUDE $(CCDEFAULTS) #\
!IF 0
-include $(CCDEFAULTS) #\
!ENDIF
