#include "Memory.h"
#include "System.h"

namespace eon {
namespace core {
    void System::start() {
        Memory::get();
    }
}}
