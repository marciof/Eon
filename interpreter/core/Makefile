.POSIX:

SRC=.
BUILD=.
CCDEFAULTS=$(CC)
LIBPREFIX=lib
LIBSUFFIX=.a

-include $(SRC)/../Makefile.$(CCDEFAULTS)

$(BUILD)/$(LIBPREFIX)karyon$(LIBSUFFIX): $(BUILD)/Err.o $(BUILD)/Log.o
	$(AR) $(ARFLAGS) $@ $(BUILD)/Err.o $(BUILD)/Log.o

$(BUILD)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/Log.o: $(SRC)/Err.h
