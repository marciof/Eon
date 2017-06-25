#include "../../core/Log.h"
#include "Boot_Device.h"

namespace eon {
namespace i386 {
namespace multiboot {
    void Boot_Device::log() {
        e_Log::get()->info(
            "Boot device: drive={iuh}; partitions=[{iuh}, {iuh}, {iuh}]",
            this->drive_number,
            this->top_level_partition,
            this->sub_partition,
            this->sub_sub_partition);
    }
}}}
