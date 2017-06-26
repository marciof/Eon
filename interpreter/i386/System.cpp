/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/Log.h"
#include "../core/System.h"
#include "multiboot/Info.h"
#include "support.h"

/**
 * Interfaces the assembly and C++ source code.
 */
extern "C" void c_main() {
    eon::i386::support::initialize();
    
    e_System* system = e_System::get();
    system->start();
    system->stop();
}

/**
 * Halts the computer.
 */
extern "C" void halt();

/**
 * Resets the computer.
 */
extern "C" void reset();

class e_System_Processor: public e_System {
public:
    void start() {
        e_Multiboot_Info::get()->log();
        e_System::start();
    }

    void stop(e_System_Stop_Mode mode) {
        switch (mode) {
        case E_SYSTEM_HALT:
            // TODO
            e_Log_get()->warning("Halt shutdown not implemented.");
            eon::i386::support::finalize();
            halt();
            break;
        case E_SYSTEM_RESET:
            eon::i386::support::finalize();
            reset();
            break;
        default:
            e_Log_error(e_Log_get(), "Invalid system stop mode.");
            break;
        }
    }
};

e_System* e_System::get() {
    static e_System_Processor system;
    return &system;
}
