#pragma once

class e_System {
public:
    enum Stop_Mode {
        HALT,
        RESET
    };

    static e_System* get(); // = 0
    virtual ~e_System() {};
    virtual void start();
    virtual void stop(Stop_Mode mode = HALT) = 0;
};
