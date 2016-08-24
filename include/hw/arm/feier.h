#include "qemu-common.h"
#include "qemu/error-report.h"
#include "hw/char/serial.h"
#include "hw/arm/arm.h"

#include "sysemu/sysemu.h"
#include "exec/address-spaces.h"

#define TYPE_FEIER "feier_soc"
#define FEIER_PIC_INT_NR	32

typedef struct FeierState {
	/*< private >*/
	DeviceState parent_obj;
	/*< public >*/

	ARMCPU cpu;
	qemu_irq irq[FEIER_PIC_INT_NR];
} FeierState;
