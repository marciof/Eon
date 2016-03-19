#pragma once

namespace eon {
namespace core {
    class System {
    public:
        enum Stop_Mode {
            HALT,
            RESET
        };

        static System* get(); // = 0
        virtual ~System() {};
        virtual void start();
        virtual void stop(Stop_Mode mode = HALT) = 0;
    };
}}
