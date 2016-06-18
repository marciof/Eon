#include "../core/memory.h"

namespace eon {
namespace native {
    class Malloc_Memory: public core::Memory {
    };
}}

namespace eon {
namespace core {
    Memory* Memory::get() {
        static native::Malloc_Memory memory;
        return &memory;
    }
}}
