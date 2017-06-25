#include "../core/Memory.h"

class e_Memory_Malloc: public e_Memory {
};

e_Memory* e_Memory::get() {
    static e_Memory_Malloc memory;
    return &memory;
}
