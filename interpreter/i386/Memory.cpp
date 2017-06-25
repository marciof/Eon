#include <stdint.h>
#include "../core/Memory.h"
#include "bit.h"

#define CONCAT(x, y) x##y
#define CONCAT_EXPAND(x, y) CONCAT(x, y)

// http://www.pixelbeat.org/programming/gcc/static_assert.html
#define STATIC_ASSERT(expr, message) \
    enum {CONCAT_EXPAND(STATIC_ASSERTION_, __LINE__) = 1 / ((expr) ? 1 : 0)}

/**
 * Loads the GDT register.
 *
 * @param [in] size size in bytes of the GDT
 * @param [in] address starting address of the GDT
 */
extern "C" void e_Memory_Physical_set_gdtr(uint16_t size, uint32_t address);

enum Segment_Attr {
    ACCESSED = BIT(0),
    EXECUTABLE = BIT(3)
};

enum Segment_Attr_Code {
    EXECUTE_READ = BIT(1),
    CONFORMING = BIT(2)
};

enum Segment_Attr_Data {
    READ_WRITE = BIT(1),
    EXPAND_DOWN = BIT(2)
};

enum Segment_Granularity {
    /** The segment size can range from 1 B to 1 MiB. */
    STEP_1B = 0,

    /** The segment size can range from 4 KiB to 4 GiB. */
    STEP_4KiB = 1
};

enum Segment_Operation_Size {
    SEGMENT_16_BIT = 0,
    SEGMENT_32_BIT = 1
};

enum Segment_Presence {
    ABSENT = 0,
    IN_MEMORY = 1
};

enum Segment_Type {
    SYSTEM = 0,
    CODE_DATA = 1
};

PACKED_STRUCT(struct Segment_Descriptor {
    /**
     * @name Segment Limit
     * Specifies the segment size according to the granularity.
     */
    uint16_t segment_limit_low;

    /**
     * @name Base Address
     * Defines the start location of the segment.
     * @{
     */
    uint16_t base_addr_low;
    uint8_t base_addr_high_lower;
    // @}

    unsigned int attributes: 4;
    unsigned int type: 1;

    /**
     * Specifies the privilege level of the segment (DPL - Descriptor
     * Privilege Level) from 0 to 3, with 0 being the most privileged
     * level.
     */
    unsigned int privilege_level: 2;

    unsigned int presence: 1;
    unsigned int segment_limit_high: 4;    ///< @ingroup Segment Limit
    unsigned int reserved_system: 1;       ///< Always zero.
    unsigned int reserved: 1;              ///< Always zero.
    unsigned int operation_size: 1;
    unsigned int granularity: 1;
    uint8_t base_addr_high_upper;          ///< @ingroup Base Address
});

STATIC_ASSERT(sizeof(Segment_Descriptor) == 8,
    "Memory segment descriptor structure not packed.");

class e_Memory_Physical: public e_Memory {
public:
    e_Memory_Physical() {
    }
};

e_Memory* e_Memory::get() {
    static e_Memory_Physical memory;
    return &memory;
}
