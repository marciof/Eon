#pragma once

/**
 * @brief Runtime language support
 */


namespace eon {
namespace x86 {
namespace support {
    /**
     * Initializes miscellaneous support sub-systems.
     *
     * Ensures that C++ static/global constructors are called.
     */
    void initialize();
    
    
    /**
     * Finalizes miscellaneous support sub-systems.
     *
     * Ensures that C++ static/global destructors are called.
     */
    void finalize();
}}}
