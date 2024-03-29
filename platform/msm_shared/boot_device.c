/* Copyright (c) 2014-2016,2019 The Linux Foundation. All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of The Linux Foundation. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <debug.h>
#include <mmc.h>
#include <ufs.h>
#include <board.h>
#include <platform/iomap.h>
#include <boot_device.h>
#include <qpic_nand.h>

static uint32_t boot_device = BOOT_EMMC;

void platform_read_boot_config()
{
#if ENABLE_BOOT_CONFIG_SUPPORT
	boot_device = BOOT_DEVICE_MASK(readl(BOOT_CONFIG_REG));
	board_update_boot_dev(boot_device);
#endif
}

uint32_t platform_get_boot_dev()
{
	return boot_device;
}

uint8_t platform_get_boot_dev_slot_num()
{
	uint32_t val = 0;
	void *dev = target_mmc_device();
	if (!dev)
		return 0;

	val = platform_get_boot_dev();
	switch(platform_get_boot_dev())
	{
#if !USE_MDM_BOOT_CFG
		case BOOT_DEFAULT:
			return ((struct mmc_device *)dev)->config.slot;
		case BOOT_UFS:
		case BOOT_SD_ELSE_UFS:
			break; // TODO
#endif
		case BOOT_EMMC:
			return ((struct mmc_device *)dev)->config.slot;
		default:
			dprintf(CRITICAL,"ERROR: Unexpected boot_device val=%x",val);
	}

	// we should never reach here
	return 0;
}

/*
 * Return 1 if boot from emmc else 0
 */
uint32_t platform_boot_dev_isemmc()
{
	uint32_t boot_dev_type;

	boot_dev_type = platform_get_boot_dev();

#if USE_MDM_BOOT_CFG
	/* For MDM default boot device is NAND */
	if (boot_dev_type == BOOT_EMMC)
#else
	if (boot_dev_type == BOOT_EMMC || boot_dev_type == BOOT_DEFAULT)
#endif
		boot_dev_type = 1;
	else
		boot_dev_type = 0;

	return boot_dev_type;
}

/*
 * Return 1 if boot from NAND else 0
 * For MDM : If the device is not Emmc,
 *           By default : It is treated as NAND
 * For non-MDM (MSM) : If the device is neither EMMC nor UFS
 *           It will be treated as NAND.
 * BOOT_DEFAULT in case of Non-MDM targets is EMMC.
 */
uint32_t platform_boot_dev_is_nand()
{
        uint32_t val = 0;

        val = platform_get_boot_dev();
        switch(val)
        {
#if USE_MDM_BOOT_CFG
                case BOOT_EMMC:
                        return 0;
#else
                case BOOT_DEFAULT:
                case BOOT_EMMC:
                case BOOT_UFS:
                        return 0;
#endif
                default:
                        return 1;
        };
}

void platform_boot_dev_cmdline(char *buf)
{
	uint32_t val = 0;
	void *dev = target_mmc_device();

	val = platform_get_boot_dev();
	switch(val)
	{
#if !USE_MDM_BOOT_CFG
		case BOOT_DEFAULT:
			snprintf(buf, ((sizeof((struct mmc_device *)dev)->host.base)*2) + 7,"%x.sdhci", ((struct mmc_device *)dev)->host.base);
			break;
		case BOOT_UFS:
		case BOOT_SD_ELSE_UFS:
			snprintf(buf, ((sizeof((struct ufs_dev *)dev)->base)*2) + 7, "%x.ufshc", ((struct ufs_dev *)dev)->base);
			break;
#endif
		case BOOT_EMMC:
			snprintf(buf, ((sizeof((struct mmc_device *)dev)->host.base)*2) + 7,"%x.sdhci", ((struct mmc_device *)dev)->host.base);
			break;
		default:
			dprintf(CRITICAL,"ERROR: Unexpected boot_device val=%x",val);
			ASSERT(0);
	};
}
