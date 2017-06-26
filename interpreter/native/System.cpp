#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/System.h"
#include "../core/Log.h"

// FIXME: don't make argv global state
static char** _argv = NULL;

class e_System_Process: public e_System {
public:
    void stop(e_System::e_System_Stop_Mode mode) {
        switch (mode) {
        case e_System::E_SYSTEM_HALT:
            exit(EXIT_SUCCESS);
            break;
        case e_System::E_SYSTEM_RESET:
            if (execvp(_argv[0], _argv) != 0) {
                e_Log_msg(e_Log_get(), E_LOG_ERROR,
                    "System reset error: errno={i}", errno);
            }
            break;
        default:
            e_Log_msg(e_Log_get(), E_LOG_ERROR, "Invalid system stop mode.");
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
