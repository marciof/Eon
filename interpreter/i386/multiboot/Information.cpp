#include "../../core/Log.h"
#include "../../core/System.h"
#include "Boot_Device.h"
#include "Drive.h"
#include "Information.h"
#include "Memory_Region_Iterator.h"

// FIXME: refactor with BIT macros
#define IS_FLAG_SET(flags, flag) \
    (((flags) & (flag)) != 0)

namespace eon {
namespace i386 {
namespace multiboot {

    extern "C" Information* _multiboot_info;
    extern "C" uint32_t _multiboot_magic_nr;

    Information* Information::get() {
        if (_multiboot_magic_nr != MULTIBOOT_BOOTLOADER_MAGIC) {
            e_Log::get()->error(
                "Invalid Multiboot magic number: {iuh}", _multiboot_magic_nr);
        }
        
        if (IS_FLAG_SET(_multiboot_info->flags, MULTIBOOT_INFO_AOUT_SYMS)
            && IS_FLAG_SET(_multiboot_info->flags, MULTIBOOT_INFO_ELF_SHDR))
        {
            e_Log::get()->error(
                "Invalid Multiboot information: "
                "Both bits 4 and 5 of the flags field are set.");
        }
        
        return _multiboot_info;
    }

    void Information::log() {
        e_Log::get()->info("Multiboot: flags={iub}", this->flags);
        
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_MEMORY)) {
            e_Log::get()->info("Memory: lower={iu} KiB; upper={iu} KiB",
                this->mem_lower,        // From 0 to 640.
                this->mem_upper);       // Starting at 1024.
        }

        this->log_boot_device();
        
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_CMDLINE)) {
            e_Log::get()->info("Command line: \"{s}\"", this->cmdline);
        }

        this->log_boot_modules();
        this->log_symbol_table();
        this->log_memory_map();
        this->log_drives();
        
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_CONFIG_TABLE)) {
            /* ROM configuration table as returned by the "get configuration"
               BIOS call. If it failed, the size of the table must be zero. */

            e_Log::get()->info("ROM configuration: table={iuh}",
                this->config_table);
        }
        
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_BOOT_LOADER_NAME)) {
            e_Log::get()->info("Boot loader: \"{s}\"",
                this->boot_loader_name);
        }
        
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_APM_TABLE)) {
            multiboot_apm_info& table = *reinterpret_cast<multiboot_apm_info*>(
                this->apm_table);

            e_Log::get()->info("APM table: version={iu}; flags={iub}",
                table.version, table.flags);
        }

        this->log_vbe();
    }

    void Information::log_boot_device() {
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_BOOTDEV)) {
            e_Multiboot_Boot_Device& device
                = reinterpret_cast<e_Multiboot_Boot_Device&>(this->boot_device);

            device.log();
        }
    }
    
    void Information::log_boot_modules() {
        if (!IS_FLAG_SET(this->flags, MULTIBOOT_INFO_MODS)) {
            return;
        }
        
        for (size_t i = 0; i < this->mods_count; ++i) {
            multiboot_mod_list& module = reinterpret_cast<multiboot_module_t*>(
                this->mods_addr)[i];

            e_Log::get()->info(
                "Boot module: start={iuh}; end={iuh}; string=\"{s}\"",
                module.mod_start, module.mod_end,
                reinterpret_cast<char*>(module.cmdline));
        }
    }

    void Information::log_drives() {
        if (!IS_FLAG_SET(this->flags, MULTIBOOT_INFO_DRIVE_INFO)) {
            return;
        }

        Drive_Iterator iterator(reinterpret_cast<Drive*>(this->drives_addr),
            this->drives_length);
        
        while (iterator.has_next()) {
            iterator.next()->log();
        }
    }

    void Information::log_memory_map() {
        if (!IS_FLAG_SET(this->flags, MULTIBOOT_INFO_MEM_MAP)) {
            return;
        }
        
        Memory_Region_Iterator iterator(
            reinterpret_cast<multiboot_mmap_entry*>(this->mmap_addr),
            this->mmap_length);
        
        // The memory map is provided by the BIOS and is guaranteed to list
        // all standard memory that should be available for normal use.

        while (iterator.has_next()) {
            multiboot_mmap_entry* region = iterator.next();

            e_Log::get()->info("Memory map region: addr=[{iuh}, {iuh}]; "
                "size=[{iuh}, {iuh}] B; type={iu}",
                static_cast<unsigned>(region->addr >> 32),
                static_cast<unsigned>(region->addr & 0xFFFFFFFF),
                static_cast<unsigned>(region->len >> 32),
                static_cast<unsigned>(region->len & 0xFFFFFFFF),
                region->type);
        }
    }

    void Information::log_symbol_table() {
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_AOUT_SYMS)) {
            multiboot_aout_symbol_table& table = this->u.aout_sym;

            e_Log::get()->info("a.out symbol table: "
                "size={iu}; string table size={iu}; addr={iuh}",
                table.tabsize, table.strsize, table.addr);
        }
        else if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_ELF_SHDR)) {
            multiboot_elf_section_header_table& table = this->u.elf_sec;

            e_Log::get()->info("ELF section header table: "
                "num={iu}; size={iu} B; addr={iuh}; shndx={iu}",
                table.num, table.size, table.addr, table.shndx);
        }
    }
    
    void Information::log_vbe() {
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_VBE_INFO)) {
            e_Log::get()->info("VBE: control info={iuh}; mode info={iuh}; "
                "current video mode={iu}",
                this->vbe_control_info,     // Obtained by VBE function 00h.
                this->vbe_mode_info,        // Obtained by VBE function 01h.
                this->vbe_mode);            // In VBE 3.0 format.
        }
        
        if (IS_FLAG_SET(this->flags, MULTIBOOT_INFO_FRAMEBUFFER_INFO)) {
            /* The following fields contain the table of a protected mode
               interface defined in VBE version 2.0 or later. If it isn't
               available, those fields are set to zero. */

            e_Log::get()->info("VBE 2.0+ interface table: segment={iuh}; "
                "offset={iuh}; length={iu} B", this->vbe_interface_seg,
                this->vbe_interface_off, this->vbe_interface_len);
        }
    }
}}}
