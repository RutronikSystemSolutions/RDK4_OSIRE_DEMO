/*****************************************************************************
 * Copyright 2022 by ams OSRAM AG                                            *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************/

/*****************************************************************************/
/*****************************************************************************/
//#include <Hal/Gpios/inc/pin.h>
//#include <Hal/Flash/inc/flash.h>
//#include <Hal/Spi/inc/spiMaster.h>
//#include <Hal/Spi/inc/spiSlave.h>
#include <System/inc/initSystem.h>
//#include <Hal/Timer/inc/timer.h>
//#include <Hal/Uart/inc/genericUart.h>
//#include <Hal/Uart/inc/uart.h>
//#include <SwTimer/inc/swTimer.h>
//#include <Driver/SPI/inc/spiMasterTimerDriver.h>
//#include <Hal/Flash/inc/flash.h>

#include <osire_sources/Hal/CY_Gpios/inc/pin.h>
#include <osire_sources/HAL/CY_SPI/inc/SpiMaster.h>
#include <osire_sources/HAL/CY_Flash_EEPROM/inc/flash.h>

/*****************************************************************************/
/*****************************************************************************/
void hal_init_clk (void)
{
//  CLOCK_SYS_Init (g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
//                  g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
//  CLOCK_SYS_UpdateConfiguration (0U, CLOCK_MANAGER_POLICY_AGREEMENT);
}

/*****************************************************************************/
/*****************************************************************************/
void reset_wdt (void)
{
  //WDOG_DRV_Trigger (WATCHDOG1_INST);
}

/*****************************************************************************/
/*****************************************************************************/
void lptmrISR (void)
{
//  hal_clearISR_timer_SPI_send ();
}

/*****************************************************************************/
/*****************************************************************************/
void init_sys (void)
{
//  hal_init_clk ();
//  hal_init_pin ();
//
  set_led_blue (0); //set LED to OFF or else they will light up
  set_led_red (0);
  set_led_green (0);
//
//  hal_init_timer_SPI_send ((isr_t) get_spi_timer_intHandler ());
//  hal_init_timer_SW_timer ((isr_t) get_sw_timer_intHandler ());
//
  CY_init_SPI_Master();
//  hal_spi_slave_init ();
  hal_init_flash ();
//  hal_uart_init ();
//  start_uart_receive ();
}

