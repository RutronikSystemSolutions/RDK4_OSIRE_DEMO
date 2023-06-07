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

//#include <Common/inc/osireEvkDefines.h>
#include <Hal/CY_Spi/inc/spiGeneral.h>
#include <Hal/CY_Spi/inc/spiMaster.h>
#include <Hal/CY_Spi/inc/spiSlave.h>
//#include <SwTimer/inc/swTimer.h>
#include "Manchester/inc/manchester.h"
//#include <Driver/SPI/inc/spiMasterTimerDriver.h>

errorSpi_t spiHalError = NO_ERROR_SPI;
//status_t spiHalNxpError = STATUS_SUCCESS;

#define ADD_DELAY_BYTE 4 //Note: Add delay is not allowed to be <=3
#define TIME_OUT_MS_FOR_ANSWER 100
#define MAX_TRY 3
/*****************************************************************************/
/*****************************************************************************/
// Function for sending only to the LEDs -> Blocking!
errorSpi_t send_data_over_spi_blocking (uint8_t *p_bufferSend, uint16_t count)
{
  errorSpi_t errorCode;
  uint8_t bufferTemp[count * 2 + 1 + ADD_DELAY_BYTE];
  uint16_t byteCount = count * 2 + 1 + ADD_DELAY_BYTE;
  manchester_encoding_buffer_swap (p_bufferSend, bufferTemp, count,sizeof(bufferTemp));

  bufferTemp[count * 2] = 0xFF; //workaround for last rising edge, first fixed delay byte

  for (uint8_t i = 1; i <= ADD_DELAY_BYTE; i++)
    {
      bufferTemp[byteCount - i] = 0xFF; //fixed Delay!
    }
  errorCode = hal_spi_master_send_blocking (bufferTemp, count * 2 + 1 + ADD_DELAY_BYTE);
  return (errorCode);
}

/*****************************************************************************/
/*****************************************************************************/
//Function for sending and receiving of Messages to and from the LED over 2
// different SPI interfaces
errorSpi_t send_and_receive_data_over_spi_blocking (uint8_t *p_bufferSend,
                                                    uint8_t *p_bufferReceive,
                                                    uint16_t countSend,
                                                    uint16_t countReceive)
{
  errorSpi_t errorCode;
  uint8_t bufferTemp[countSend * 2 + 1 /*+  ADD_DELAY_BYTE*/];
  uint16_t byteCount = countSend * 2 + 1;

  manchester_encoding_buffer_swap (p_bufferSend, bufferTemp, countSend,
                                   sizeof(bufferTemp));

  bufferTemp[countSend * 2] = 0xFF; //workaround for last rising edge, first fixed delay byte

  for (uint8_t i = 0; i <= MAX_TRY; i++)
    {
      errorCode = hal_spi_slave_receive_for_blocking (p_bufferReceive, countReceive);
      if (errorCode == NO_ERROR_SPI)
        {
          errorCode = hal_spi_master_send_blocking (bufferTemp, byteCount);
        }

      uint32_t sysTime = Cy_SysTick_GetValue ();
      //TIME_OUT_MS_FOR_ANSWER ms blocking in case we are missing some data
      uint32_t sysTimeOut = sysTime + TIME_OUT_MS_FOR_ANSWER;
      uint8_t overflow = 0;

      if (sysTimeOut < sysTime)
        {
          overflow = 1;
        }

      errorCodeSpiNewMessage_t newMessageState = SPI_NO_NEW_MESSAGE;

      while (newMessageState != SPI_NEW_MESSAGE_OK)
        {
          sysTime = Cy_SysTick_GetValue ();

          if (overflow == 0)
            {
              if (sysTime > sysTimeOut)
                {
                  errorCode = SPI_ERROR_TIME_OUT;
                  break;
                }
            }
          else
            {
              if (sysTime < sysTimeOut) //we have overrun once!
                {
                  overflow = 0;
                }
            }

          newMessageState = hal_check_for_bytes_received_for_blocking ();

          if (newMessageState == SPI_ERROR_DATA_CORRUPTION)
            {
              break;
            }
        };

      if (newMessageState != SPI_ERROR_DATA_CORRUPTION)
        {
          break;
        }
    }

  return (errorCode);
}

/*****************************************************************************/
/*****************************************************************************/
// Function for sending only to the LEDs
errorSpi_t send_data_over_spi_non_blocking (uint8_t *p_bufferSend,
                                            uint16_t count, uint32_t delay,
                                            bool restart)
{
  errorSpi_t err;
  uint8_t bufferTemp[count * 2 + 1 + ADD_DELAY_BYTE];
  uint16_t byteCount = count * 2 + 1;

  manchester_encoding_buffer_swap (p_bufferSend, bufferTemp, count,
                                   sizeof(bufferTemp));
  bufferTemp[count * 2] = 0xFF; //workaround for last rising edge, first fixed delay byte

  if (delay == 0)
    {
      byteCount += ADD_DELAY_BYTE;

      for (uint8_t i = 1; i <= ADD_DELAY_BYTE; i++)
        {
          bufferTemp[byteCount - i] = 0xFF; //fixed Delay!
        }
    }

  err = hal_spi_master_send_non_blocking (bufferTemp, byteCount, delay);

  if (err == NO_ERROR_SPI)
    {
      if (restart == true)
        {
          restart_non_blocking_spi_send ();
        }
    }

  return (err);
}

/*****************************************************************************/
/*****************************************************************************/
// Function for sending only to the LEDs
errorSpi_t send_and_receive_data_over_spi_non_blocking (uint8_t *p_bufferSend,
                                                        uint16_t count,
                                                        bool restart)
{
  errorSpi_t err;
  uint8_t bufferTemp[count * 2 + 1 + ADD_DELAY_BYTE];
  //*2 because of manchester, +1 because of workaround (last rising edge), + ADD_DELAY_BYTE for time between messages on the SP

  uint16_t byteCount = count * 2 + 1;

  manchester_encoding_buffer_swap (p_bufferSend, bufferTemp, count,
                                   sizeof(bufferTemp));
  bufferTemp[count * 2] = 0xFF; //workaround for last rising edge, first fixed delay byte

  err = hal_spi_master_send_non_blocking (bufferTemp, byteCount, 0);

  if (err == NO_ERROR_SPI)
    {
      if (restart == true)
        {
          restart_non_blocking_spi_send ();
        }
    }

  return (err);
}

errorSpi_t restart_non_blocking_spi_send (void)
{
  errorSpi_t err = spi_master_start ();
  return (err);

}

uint8_t* get_pointer_next_message_non_blocking (errorSpi_t *p_err)
{

  errorCodeSpiNewMessage_t errorSPI;

  uint8_t *p_messageBuffer = hal_get_new_message (&errorSPI);

  if (errorSPI == SPI_NEW_MESSAGE_OK)
    {
      *p_err = NO_ERROR_SPI;
    }
  else
    {
      *p_err = SPI_NO_NEW_DATA_RECEIVED;
      p_messageBuffer = NULL;
    }

  return (p_messageBuffer);
}

errorSpi_t spi_receive_control (void)
{ //Note: This function needs to be added to main.c if the non-blocking receive is used
  spiReceiveStatusSlave_t status = hal_spi_receive_control ();
  errorSpi_t err = NO_ERROR_SPI;

  if (status == SPI_RECEIVE_ERROR_CORRUPT_DATA)
    {
      err = SPI_ERROR_CORRUPT_DATA;
    }

  return (err);
}

void spi_receive_reset_buffer (void)
{
  hal_spi_receive_reset_buffer ();
}

void spi_receive_reset (void)
{
  hal_reset_spi_slave ();
}
