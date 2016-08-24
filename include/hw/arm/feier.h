#include "qemu-common.h"
#include "qemu/error-report.h"
#include "hw/char/serial.h"
#include "hw/arm/arm.h"

#include "sysemu/sysemu.h"
#include "exec/address-spaces.h"



#define TYPE_FEIER "feier_soc"
#define FEIER_PIC_INT_NR	32

#define FEIER(obj) OBJECT_CHECK(FeierState, (obj), TYPE_FEIER)

typedef struct FeierState {
	/*< private >*/
	DeviceState parent_obj;
	/*< public >*/

	ARMCPU cpu;
	qemu_irq irq[FEIER_PIC_INT_NR];
} FeierState;

#define FEIER_RAM_SIZE			0x04000000	// 64MB
#define FEIER_RAM_BASE_ADDR		0x00000000
