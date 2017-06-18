#include <stdint.h>
#include "../core/memory.h"
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
extern "C" void set_gdtr(uint16_t size, uint32_t address);

namespace eon {
namespace i386 {
    namespace Segment {
        namespace Attribute {
            enum {
                ACCESSED = BIT(0),
                EXECUTABLE = BIT(3)
            };
            
            namespace Code {
                enum {
                    EXECUTE_READ = BIT(1),
                    CONFORMING = BIT(2)
                };
            }
            
            namespace Data {
                enum {
                    READ_WRITE = BIT(1),
                    EXPAND_DOWN = BIT(2)
                };
            }
        }

        namespace Granularity {
            enum {
                /** The segment size can range from 1 B to 1 MiB. */
                STEP_1B = 0,
                
                /** The segment size can range from 4 KiB to 4 GiB. */
                STEP_4KiB = 1
            };
        }

        namespace Operation_Size {
            enum {
                SEGMENT_16_BIT = 0,
                SEGMENT_32_BIT = 1
            };
        }

        namespace Presence {
            enum {
                ABSENT = 0,
                IN_MEMORY = 1
            };
        }

        namespace Type {
            enum {
                SYSTEM = 0,
                CODE_DATA = 1
            };
        }

        PACKED_STRUCT(struct Descriptor {
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
        
        STATIC_ASSERT(sizeof(Descriptor) == 8,
            "Memory segment descriptor structure not packed.");
    }

    class Physical_Memory: public core::Memory {
    public:
        Physical_Memory() {
        }
    };
}}

namespace eon {
namespace core {
    Memory* Memory::get() {
        static i386::Physical_Memory memory;
        return &memory;
    }
}}
