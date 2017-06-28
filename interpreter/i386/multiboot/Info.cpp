#include <stddef.h>
#include <stdint.h>
#include "../Bit.h"
#include "Info.h"

// FIXME: refactor with BIT macros
#define IS_FLAG_SET(flags, flag) \
    (((flags) & (flag)) != 0)

extern "C" multiboot_info* e_multiboot_info;
extern "C" uint32_t e_multiboot_magic_nr;

typedef uint8_t Drive_Access_Mode;
enum {
    // Traditional Cylinder/Head/Sector addressing mode.
    DRIVE_CHS_MODE = 0,

    // Logical Block Addressing mode.
    DRIVE_LBA_MODE = 1
};

// As read by the BIOS INT 13h disk interface.
typedef uint8_t Drive_BIOS_Nr;
enum {
    DRIVE_FIRST_DISKETTE_DRIVE = 0,
    DRIVE_FIRST_HARD_DISK_DRIVE = 0x80
};

E_BIT_ATTR_PACKED(struct Drive {
    // Size doesn't equal `10 + 2 * nr. ports` due to alignment.
    uint32_t size;

    Drive_BIOS_Nr number;
    Drive_Access_Mode access_mode;
    uint16_t cylinders;
    uint8_t heads;
    uint8_t sectors;

    // Array (ending in NULL) of I/O ports used for the drive in the BIOS
    // code. This array may contain any number of I/O ports that are not
    // related to the drive actually (such as DMA controllers' ports).
    uint16_t* ports;
});

E_BIT_ATTR_PACKED(struct Boot_Device {
    // Partition numbers start at zero.
    enum {BOOT_DEVICE_UNUSED_PARTITION = 0xFF};

    uint8_t sub_sub_partition;
    uint8_t sub_partition;
    uint8_t top_level_partition;
    Drive_BIOS_Nr drive_number;
});

static void log_boot_device(struct multiboot_info* info, struct e_Log* log) {
    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_BOOTDEV)) {
        Boot_Device& device = reinterpret_cast<Boot_Device&>(info->boot_device);

        e_Log_msg(log, E_LOG_INFO,
            "Boot device: drive={iuh}; partitions=[{iuh}, {iuh}, {iuh}]",
            device.drive_number,
            device.top_level_partition,
            device.sub_partition,
            device.sub_sub_partition);
    }
}

static void log_boot_modules(struct multiboot_info* info, struct e_Log* log) {
    if (!IS_FLAG_SET(info->flags, MULTIBOOT_INFO_MODS)) {
        return;
    }

    for (size_t i = 0; i < info->mods_count; ++i) {
        multiboot_mod_list& module = reinterpret_cast<multiboot_module_t*>(
            info->mods_addr)[i];

        e_Log_msg(log, E_LOG_INFO,
            "Boot module: start={iuh}; end={iuh}; string=\"{s}\"",
            module.mod_start, module.mod_end,
            reinterpret_cast<char*>(module.cmdline));
    }
}

static void log_drives(struct multiboot_info* info, struct e_Log* log) {
    if (!IS_FLAG_SET(info->flags, MULTIBOOT_INFO_DRIVE_INFO)) {
        return;
    }

    Drive* array = reinterpret_cast<Drive*>(info->drives_addr);
    size_t size_bytes = info->drives_length;
    size_t position = 0;

    while (position < size_bytes) {
        uint8_t* address = reinterpret_cast<uint8_t*>(array) + position;
        Drive* drive = reinterpret_cast<Drive*>(address);

        position += drive->size;

        e_Log_msg(e_Log_get(), E_LOG_INFO,
            "Drive: nr={iu}; mode={iu}; cylinders={iu}; "
                "heads={iu}; sectors={iu}; ports={iuh}",
            drive->number, drive->access_mode, drive->cylinders,
            drive->heads, drive->sectors, drive->ports);
    }
}

static void log_memory_map(struct multiboot_info* info, struct e_Log* log) {
    if (!IS_FLAG_SET(info->flags, MULTIBOOT_INFO_MEM_MAP)) {
        return;
    }

    multiboot_mmap_entry* array = reinterpret_cast<multiboot_mmap_entry*>(info->mmap_addr);
    size_t size_bytes = info->mmap_length;
    size_t position = 0;

    // The memory map is provided by the BIOS and is guaranteed to list
    // all standard memory that should be available for normal use.

    while (position < size_bytes) {
        uint8_t* address = reinterpret_cast<uint8_t*>(array) + position;
        multiboot_mmap_entry* region = reinterpret_cast<multiboot_mmap_entry*>(address);

        position += sizeof(region->size) + region->size;

        e_Log_msg(log, E_LOG_INFO, "Memory map region: addr=[{iuh}, {iuh}]; "
            "size=[{iuh}, {iuh}] B; type={iu}",
            static_cast<unsigned>(region->addr >> 32),
            static_cast<unsigned>(region->addr & 0xFFFFFFFF),
            static_cast<unsigned>(region->len >> 32),
            static_cast<unsigned>(region->len & 0xFFFFFFFF),
            region->type);
    }
}

static void log_symbol_table(struct multiboot_info* info, struct e_Log* log) {
    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_AOUT_SYMS)) {
        multiboot_aout_symbol_table& table = info->u.aout_sym;

        e_Log_msg(log, E_LOG_INFO, "a.out symbol table: "
            "size={iu}; string table size={iu}; addr={iuh}",
            table.tabsize, table.strsize, table.addr);
    }
    else if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_ELF_SHDR)) {
        multiboot_elf_section_header_table& table = info->u.elf_sec;

        e_Log_msg(log, E_LOG_INFO, "ELF section header table: "
            "num={iu}; size={iu} B; addr={iuh}; shndx={iu}",
            table.num, table.size, table.addr, table.shndx);
    }
}

static void log_vbe(struct multiboot_info* info, struct e_Log* log) {
    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_VBE_INFO)) {
        e_Log_msg(log, E_LOG_INFO, "VBE: control info={iuh}; mode info={iuh}; "
            "current video mode={iu}",
            info->vbe_control_info,     // Obtained by VBE function 00h.
            info->vbe_mode_info,        // Obtained by VBE function 01h.
            info->vbe_mode);            // In VBE 3.0 format.
    }

    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_FRAMEBUFFER_INFO)) {
        /* The following fields contain the table of a protected mode
           interface defined in VBE version 2.0 or later. If it isn't
           available, those fields are set to zero. */

        e_Log_msg(log, E_LOG_INFO, "VBE 2.0+ interface table: segment={iuh}; "
            "offset={iuh}; length={iu} B", info->vbe_interface_seg,
            info->vbe_interface_off, info->vbe_interface_len);
    }
}

struct multiboot_info* e_Multiboot_Info_get() {
    if (e_multiboot_magic_nr != MULTIBOOT_BOOTLOADER_MAGIC) {
        e_Log_msg(e_Log_get(), E_LOG_ERROR,
            "Invalid Multiboot magic number: {iuh}", e_multiboot_magic_nr);
    }

    if (IS_FLAG_SET(e_multiboot_info->flags, MULTIBOOT_INFO_AOUT_SYMS)
        && IS_FLAG_SET(e_multiboot_info->flags, MULTIBOOT_INFO_ELF_SHDR))
    {
        e_Log_msg(e_Log_get(), E_LOG_ERROR,
            "Invalid Multiboot information: "
                "Both bits 4 and 5 of the flags field are set.");
    }

    return e_multiboot_info;
}

void e_Multiboot_Info_log(struct multiboot_info* info, struct e_Log* log) {
    e_Log_msg(log, E_LOG_INFO, "Multiboot: flags={iub}", info->flags);

    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_MEMORY)) {
        e_Log_msg(log, E_LOG_INFO, "Memory: lower={iu} KiB; upper={iu} KiB",
            info->mem_lower,        // From 0 to 640.
            info->mem_upper);       // Starting at 1024.
    }

    log_boot_device(info, log);

    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_CMDLINE)) {
        e_Log_msg(log, E_LOG_INFO, "Command line: \"{s}\"", info->cmdline);
    }

    log_boot_modules(info, log);
    log_symbol_table(info, log);
    log_memory_map(info, log);
    log_drives(info, log);

    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_CONFIG_TABLE)) {
        /* ROM configuration table as returned by the "get configuration"
           BIOS call. If it failed, the size of the table must be zero. */

        e_Log_msg(log, E_LOG_INFO, "ROM configuration: table={iuh}",
            info->config_table);
    }

    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_BOOT_LOADER_NAME)) {
        e_Log_msg(log, E_LOG_INFO, "Boot loader: \"{s}\"",
            info->boot_loader_name);
    }

    if (IS_FLAG_SET(info->flags, MULTIBOOT_INFO_APM_TABLE)) {
        multiboot_apm_info& table = *reinterpret_cast<multiboot_apm_info*>(
            info->apm_table);

        e_Log_msg(log, E_LOG_INFO, "APM table: version={iu}; flags={iub}",
            table.version, table.flags);
    }

    log_vbe(info, log);
}
