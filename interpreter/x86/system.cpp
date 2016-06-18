/**
 * @see http://www.intel.com/products/processor/manuals/
 */


#include "../core/util.h"
#include "../core/log.h"
#include "../core/system.h"
#include "multiboot/information.h"
#include "support.h"


/**
 * Interfaces the assembly and C++ source code.
 */
extern "C" void c_main() {
    eon::x86::support::initialize();
    
    eon::core::System* system = eon::core::System::get();
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


namespace eon {
namespace x86 {
    class Processor_System: public core::System {
    public:
        void start() {
            multiboot::Information::get()->log();
            core::System::start();
        }
        
        
        void stop(Stop_Mode mode) {
            switch (mode) {
            case HALT:
                // TODO
                core::Log::get()->warning("Halt shutdown not implemented.");
                support::finalize();
                halt();
                break;
            case RESET:
                support::finalize();
                reset();
                break;
            default:
                core::Log::get()->error("Invalid system stop mode.");
                break;
            }
        }
    };
}}


namespace eon {
namespace core {
    System* System::get() {
        static x86::Processor_System system;
        return &system;
    }
}}
