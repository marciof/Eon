#include "../../core/Log.h"
#include "Boot_Device.h"

namespace eon {
namespace x86 {
namespace multiboot {
    void Boot_Device::log() {
        core::Log::get()->info(
            "Boot device: drive={iuh}; partitions=[{iuh}, {iuh}, {iuh}]",
            this->drive_number,
            this->top_level_partition,
            this->sub_partition,
            this->sub_sub_partition);
    }
}}}
