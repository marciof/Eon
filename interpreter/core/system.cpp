#include "memory.h"
#include "system.h"

namespace eon {
namespace core {
    void System::start() {
        e_Memory::get();
    }
}}
