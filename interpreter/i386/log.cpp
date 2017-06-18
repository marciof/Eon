#include "../core/log.h"
#include "vga/text_mode.h"

namespace eon {
namespace i386 {
    class Vga_Log: public core::Log {
    public:
        Vga_Log() {
            vga::text_mode::initialize();
        }

    protected:
        void prepare_error() {
            vga::text_mode::set_color(vga::text_mode::RED);
        }

        void prepare_info() {
            vga::text_mode::set_color(vga::text_mode::WHITE);
        }

        void prepare_warning() {
            vga::text_mode::set_color(vga::text_mode::YELLOW);
        }

        void print(char ch) {
            vga::text_mode::print(ch);
        }

        void print(const char* string) {
            vga::text_mode::print(string);
        }
    };
}}

namespace eon {
namespace core {
    Log* Log::get() {
        static i386::Vga_Log log;
        return &log;
    }
}}
