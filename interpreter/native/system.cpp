#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/system.h"
#include "../core/log.h"

namespace eon {
namespace native {
    static char** _argv = NULL;

    class Process_System: public core::System {
    public:
        void stop(core::System::Stop_Mode mode) {
            switch (mode) {
            case core::System::HALT:
                exit(EXIT_SUCCESS);
                break;
            case core::System::RESET:
                if (execvp(_argv[0], _argv) != 0) {
                    e_Log::get()->error("System reset error: errno={i}",
                        errno);
                }
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
        static native::Process_System system;
        return &system;
    }
}}

int main(int argc, char* argv[]) {
    eon::native::_argv = argv;
    eon::core::System* system = eon::core::System::get();
    
    system->start();
    system->stop();
    
    return EXIT_FAILURE;
}
