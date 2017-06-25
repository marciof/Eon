#pragma once
#include <stdarg.h>
#include <stddef.h>

/**
 * Log format is a regular string with placeholders denoted by curly braces.
 *
 * Inside each curly brace is a conversion specifier:
 * - "c": character
 * - "s": string or `NULL`
 * - "i": integer
 *   - with "u": unsigned
 *   - with one of:
 *     - "b": base 2
 *     - "h": base 16
 *     - none: base 10
 *
 * To print a literal curly brace, repeat it twice.
 */
class e_Log {
public:
    enum {TAB_NR_SPACES = 4};
    static e_Log* get(); // = 0
    virtual ~e_Log() {};
    void error(const char* format, ...);
    void info(const char* format, ...);
    void warning(const char* format, ...);

protected:
    virtual void prepare_error();
    virtual void prepare_info();
    virtual void prepare_warning();
    virtual void print(char ch) = 0;
    virtual void print(const char* string) = 0;

private:
    void print(unsigned int integer, size_t base);
    void print(const char* format, va_list arguments);
};
