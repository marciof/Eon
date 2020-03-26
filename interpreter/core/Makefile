.POSIX:

OUTPUT=.
CCDEFAULTS=$(CC)
LIBPREFIX=lib
LIBSUFFIX=.a

-include ../Makefile.$(CCDEFAULTS)

$(OUTPUT)/$(LIBPREFIX)karyon$(LIBSUFFIX): $(OUTPUT)/Err.o $(OUTPUT)/Log.o
	$(AR) $(ARFLAGS) $@ $(OUTPUT)/Err.o $(OUTPUT)/Log.o

$(OUTPUT)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

Log.o: Err.h
