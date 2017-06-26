#pragma once

class e_System {
public:
    enum e_System_Stop_Mode {
        E_SYSTEM_HALT,
        E_SYSTEM_RESET
    };

    static e_System* get(); // = 0
    virtual ~e_System() {};
    virtual void start();
    virtual void stop(e_System_Stop_Mode mode = E_SYSTEM_HALT) = 0;
};
