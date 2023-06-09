/*
 * flash.h
 *
 *  Created on: 08.06.2023
 *      Author: EDE
 */

#ifndef OSIRE_SOURCES_HAL_CY_FLASH_EEPROM_INC_FLASH_H_
#define OSIRE_SOURCES_HAL_CY_FLASH_EEPROM_INC_FLASH_H_



#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_em_eeprom.h"




#ifdef __cplusplus
extern "C" {
#endif

cy_en_em_eeprom_status_t hal_erase_led_xyz_data_from_flash (void);
cy_en_em_eeprom_status_t hal_write_single_led_xyz_struct_to_flash (uint16_t ledIndex,const uint8_t *p_bufSrc,uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* OSIRE_SOURCES_HAL_CY_FLASH_EEPROM_INC_FLASH_H_ */
