/*
 * Feiboard emulation
 *
 * Copyright (C) 2016 Peter Kung
 * Written by Peter Kung <peterkoug@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "cpu.h"
#include "hw/sysbus.h"
#include "hw/devices.h"
#include "hw/boards.h"
#include "hw/arm/feier.h"

static struct arm_boot_info feiboard_binfo;

typedef struct FeiBoardState {
	FeierState soc;
	MemoryRegion ram;
} FeiBoardState;

static void feiboard_init(MachineState *machine)
{
	FeiBoardState *s = g_new(FeiBoardState, 1);

	object_initialize(&s->soc, sizeof(s->soc), TYPE_FEIER);
	object_property_add_child(OBJECT(machine), "soc", OBJECT(&s->soc),
			&error_abort);

	object_property_set_bool(OBJECT(&s->soc), true, "realized", &error_fatal);

	machine->ram_size = FEIER_RAM_SIZE;
	memory_region_allocate_system_memory(&s->ram, NULL, "feiboard.ram",
    							machine->ram_size);
	memory_region_add_subregion(get_system_memory(), FEIER_RAM_BASE_ADDR, &s->ram);

	feiboard_binfo.ram_size = machine->ram_size;
	feiboard_binfo.kernel_filename = machine->kernel_filename;
	feiboard_binfo.kernel_cmdline = machine->kernel_cmdline;
	feiboard_binfo.initrd_filename = machine->initrd_filename;
	feiboard_binfo.board_id = 0x0118;
	feiboard_binfo.loader_start = FEIER_RAM_BASE_ADDR;
	arm_load_kernel(&s->soc.cpu, &feiboard_binfo);

#if 0
    CubieBoardState *s = g_new(CubieBoardState, 1);
    Error *err = NULL;

    s->a10 = AW_A10(object_new(TYPE_AW_A10));

    object_property_set_int(OBJECT(&s->a10->emac), 1, "phy-addr", &err);
    if (err != NULL) {
        error_reportf_err(err, "Couldn't set phy address: ");
        exit(1);
    }

    object_property_set_int(OBJECT(&s->a10->timer), 32768, "clk0-freq", &err);
    if (err != NULL) {
        error_reportf_err(err, "Couldn't set clk0 frequency: ");
        exit(1);
    }

    object_property_set_int(OBJECT(&s->a10->timer), 24000000, "clk1-freq",
                            &err);
    if (err != NULL) {
        error_reportf_err(err, "Couldn't set clk1 frequency: ");
        exit(1);
    }

    object_property_set_bool(OBJECT(s->a10), true, "realized", &err);
    if (err != NULL) {
        error_reportf_err(err, "Couldn't realize Allwinner A10: ");
        exit(1);
    }

    memory_region_allocate_system_memory(&s->sdram, NULL, "cubieboard.ram",
                                         machine->ram_size);
    memory_region_add_subregion(get_system_memory(), AW_A10_SDRAM_BASE,
                                &s->sdram);

    cubieboard_binfo.ram_size = machine->ram_size;
    cubieboard_binfo.kernel_filename = machine->kernel_filename;
    cubieboard_binfo.kernel_cmdline = machine->kernel_cmdline;
    arm_load_kernel(&s->a10->cpu, &cubieboard_binfo);
#endif
}

static void feiboard_machine_init(MachineClass *mc)
{
	mc->desc = "pTech feiboard";
	mc->init = feiboard_init;
}
DEFINE_MACHINE("feiboard", feiboard_machine_init)
