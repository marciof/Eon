#pragma once


namespace eon {
namespace core {
    class Memory {
    public:
        static Memory* get(); // = 0
        virtual ~Memory() {};
    };
}}
