#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/system.h"
#include "../core/log.h"

// FIXME: don't make argv global state
static char** _argv = NULL;

class e_System_Process: public e_System {
public:
    void stop(e_System::Stop_Mode mode) {
        switch (mode) {
        case e_System::HALT:
            exit(EXIT_SUCCESS);
            break;
        case e_System::RESET:
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

e_System* e_System::get() {
    static e_System_Process system;
    return &system;
}

int main(int argc, char* argv[]) {
    _argv = argv;
    e_System* system = e_System::get();
    
    system->start();
    system->stop();
    
    return EXIT_FAILURE;
}
