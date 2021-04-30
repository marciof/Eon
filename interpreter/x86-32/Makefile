.POSIX:

# Workaround for include-line support on both `make` and `nmake`.
#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

# TODO add CFLAGS_EXTRA to other configs (other than Makefile.gcc)
CFLAGS_EXTRA=-fno-exceptions -nostdlib -nodefaultlibs -ffreestanding -m32
EXT_DEPS=../core/$(LIBPREFIX)karyon-core$(LIB)
LIB_DEPS=Memory$(OBJ) Multiboot$(OBJ) vga/Attr$(OBJ) vga/Color$(OBJ) vga/CRT$(OBJ) vga/Extern$(OBJ) vga/Gfx$(OBJ) vga/Log$(OBJ) vga/Seqr$(OBJ) vga/Text$(OBJ)
WATCHEXEC=watchexec

all: $(LIB_DEPS)

dev:
	$(WATCHEXEC) --exts c,h $(MAKE) all $(MAKEFLAGS)

Memory$(OBJ): $(EXT_DEPS)
Multiboot$(OBJ): $(EXT_DEPS) Multiboot.h
vga/Attr$(OBJ): $(EXT_DEPS) vga/Attr.h vga/Extern.h IO.h
vga/Color$(OBJ): $(EXT_DEPS) vga/Color.h IO.h
vga/CRT$(OBJ): $(EXT_DEPS) vga/CRT.h vga/Text.h IO.h
vga/Extern$(OBJ): $(EXT_DEPS) vga/Extern.h IO.h
vga/Gfx$(OBJ): $(EXT_DEPS) vga/Gfx.h IO.h
vga/Log$(OBJ): $(EXT_DEPS) vga/Log.h vga/Text.h
vga/Seqr$(OBJ): $(EXT_DEPS) vga/Seqr.h IO.h
vga/Text$(OBJ): $(EXT_DEPS) vga/Text.h vga/Attr.h vga/CRT.h vga/Extern.h vga/Gfx.h
