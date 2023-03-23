/* SPDX-License-Identifier: GPL-2.0-only */

#include <amdblocks/cpu.h>
#include <types.h>

/* Value defined in Serial VID Interface 3.0 spec (#56413, NDA only) */
#define  SERIAL_VID_3_DECODE_MICROVOLTS	5000
#define  SERIAL_VID_3_BASE_MICROVOLTS	245000L

uint32_t get_uvolts_from_vid(uint16_t core_vid)
{
	if (core_vid == 0x00) {
		/* Voltage off for VID code 0x00 */
		return 0;
	} else {
		return SERIAL_VID_3_BASE_MICROVOLTS +
			(SERIAL_VID_3_DECODE_MICROVOLTS * core_vid);
	}
}
