#include "../core/Log.h"
#include "support.h"

#if defined(__GNUC__) || defined(DOXYGEN)
#   include <cxxabi.h>
#   define MAX_AT_EXIT_ENTRIES 128

/**
 * C++ ABI support
 *
 * @see http://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/
 */
namespace __cxxabiv1 {
    struct At_Exit_Entry {
        __cxa_cdtor_type destructor;
        void* object;
        void* dso_handle;
    };

    /**
     * Dynamic Shared Object handle.
     */
    extern "C" void* __dso_handle;
    void* __dso_handle = NULL;

    static At_Exit_Entry _at_exit_entries[MAX_AT_EXIT_ENTRIES];
    static size_t _at_exit_entries_length = 0;
    
    extern "C" int __cxa_atexit(
        __cxa_cdtor_type destructor,
        void* object,
        void* dso_handle)
    _GLIBCXX_NOTHROW
    {
        if (_at_exit_entries_length >= MAX_AT_EXIT_ENTRIES) {
            e_Log_msg(e_Log_get(), E_LOG_ERROR,
                "Maximum number of C++ ABI at-exit entries reached: {iu}",
                MAX_AT_EXIT_ENTRIES);
        }
        
        _at_exit_entries[_at_exit_entries_length].destructor = destructor;
        _at_exit_entries[_at_exit_entries_length].object = object;
        _at_exit_entries[_at_exit_entries_length].dso_handle = dso_handle;
        
        ++_at_exit_entries_length;
        return 0;
    }

    /**
     * @param destructor `NULL` indicates it should finalize all objects
     */
    extern "C" int __cxa_finalize(void* destructor) {
        // FIXME
        e_Log_msg(e_Log_get(), E_LOG_WARN,
            "C++ ABI object finalization not implemented: destructor={iuh}",
            destructor);

        return 0;
    }

    extern "C" int __cxa_guard_acquire(__guard* guard) {
        return !_GLIBCXX_GUARD_TEST(guard);
    }

    extern "C" void __cxa_guard_release(__guard* guard) {
        _GLIBCXX_GUARD_SET(guard);
    }
    
    extern "C" void __cxa_guard_abort(__guard* guard) {
        e_Log_msg(e_Log_get(), E_LOG_ERROR, "C++ ABI guard abort: guard={iuh}",
            *(unsigned int*)guard);
    }

    /**
     * Handle pure virtual function calls, when the associated virtual table
     * pointer is not filled in.
     */
    extern "C" void __cxa_pure_virtual() {
        e_Log_msg(e_Log_get(), E_LOG_ERROR,
            "C++ ABI pure virtual function call.");
        __builtin_unreachable();
    }
}

#endif

typedef void (*Constructor)();
typedef void (*Destructor)();

extern "C" Constructor _cpp_ctors_begin[], _cpp_ctors_end[];
extern "C" Destructor _cpp_dtors_begin[], _cpp_dtors_end[];

void operator delete(void* object) {
    e_Log_msg(e_Log_get(), E_LOG_INFO,
        "C++ operator delete not implemented: object={iuh}", object);
}

namespace eon {
namespace i386 {
namespace support {
    void initialize() {
        for (Constructor* ctor = _cpp_ctors_begin; ctor < _cpp_ctors_end; ++ctor){
            (*ctor)();
        }
    }

    // Finalization functions are called in reverse order of their registration.
    void finalize() {
        for (Destructor* dtor = _cpp_dtors_begin; dtor < _cpp_dtors_end; ++dtor) {
            (*dtor)();
        }

        __cxxabiv1::__cxa_finalize(NULL);
    }
}}}
