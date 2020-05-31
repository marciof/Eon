.POSIX:

SRC=.
OUT=.
CCDEFAULTS=$(SRC)/../Makefile.$(CC)
LIBPREFIX=lib
LIBSUFFIX=.a

$(OUT)/$(LIBPREFIX)karyon$(LIBSUFFIX): $(OUT)/Err.o $(OUT)/Log.o
	$(AR) $(ARFLAGS) $@ $(OUT)/Err.o $(OUT)/Log.o

$(OUT)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/Log.o: $(SRC)/Err.h

-include $(CCDEFAULTS)
