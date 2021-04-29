.POSIX:

#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

# TODO missing CFLAGS_EXTRA from other configs (other than Makefile.gcc)
CFLAGS_EXTRA=-fno-exceptions -nostdlib -nodefaultlibs -ffreestanding
EXT_DEPS=../core/$(LIBPREFIX)karyon-core$(LIB)
LIB_DEPS=Memory$(OBJ) Multiboot$(OBJ)

all: $(LIB_DEPS)

Memory$(OBJ): Memory.c $(EXT_DEPS)
Multiboot$(OBJ): Multiboot.c Multiboot.h $(EXT_DEPS)
