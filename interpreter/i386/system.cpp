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
namespace i386 {
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
                e_Log::get()->warning("Halt shutdown not implemented.");
                support::finalize();
                halt();
                break;
            case RESET:
                support::finalize();
                reset();
                break;
            default:
                e_Log::get()->error("Invalid system stop mode.");
                break;
            }
        }
    };
}}


namespace eon {
namespace core {
    System* System::get() {
        static i386::Processor_System system;
        return &system;
    }
}}
