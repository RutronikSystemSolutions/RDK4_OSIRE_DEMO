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

/*
 * osire.c
 *
 *  @date 14.04.2022
 *  @autor cker
 */


#include <Hal/Osire/inc/osire.h>


#define WITH_INTERNAL_PULL_UP 0 // 1= internal pull up , 0 = external pull up

void hal_reset_osire_start (void)
{
//  set_led_CS_Slave (1);
//  PORTE->PCR[15u] = 0x0300; //no internal pull up
//  set_ext_pull_up_invalid (); //no external pull up
}

void hal_reset_osire_end (void)
{
//  delay_ms (2);
//#if (WITH_INTERNAL_PULL_UP == 0)
//  set_ext_pull_up_valid();
//#else
//  PORTE->PCR[15u] = 0x0303;
//#endif
//  delay_ms (2);
//  set_led_CS_Slave (0);
}
