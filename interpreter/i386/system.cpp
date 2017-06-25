/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/log.h"
#include "../core/system.h"
#include "multiboot/information.h"
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
        eon::i386::multiboot::Information::get()->log();
        e_System::start();
    }

    void stop(Stop_Mode mode) {
        switch (mode) {
        case HALT:
            // TODO
            e_Log::get()->warning("Halt shutdown not implemented.");
            eon::i386::support::finalize();
            halt();
            break;
        case RESET:
            eon::i386::support::finalize();
            reset();
            break;
        default:
            e_Log::get()->error("Invalid system stop mode.");
            break;
        }
    }
};

e_System* e_System::get() {
    static e_System_Processor system;
    return &system;
}
