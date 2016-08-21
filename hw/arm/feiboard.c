#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "cpu.h"
#include "hw/sysbus.h"
#include "hw/devices.h"
#include "hw/boards.h"

static void feiboard_init(MachineState *machine)
{

}

static void feiboard_machine_init(MachineClass *mc)
{
    mc->desc = "pTech feiboard";
    mc->init = feiboard_init;
}

DEFINE_MACHINE("feiboard", feiboard_machine_init)
