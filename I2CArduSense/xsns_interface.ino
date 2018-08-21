/*
  xsns_interface.ino - Sensor interface support for Sonoff-Tasmota to connect
                       external devices to an arduino board and deliver JSON responses
                       back to Sonoff-Tasmota firmware for further processing

  Copyright (C) 2018  Andre Thomas & Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
 */

boolean (* const xsns_func_ptr[])(byte) PROGMEM = {  // Sensor Function Pointers for simple implementation of sensors

#ifdef XSNS_01
  &Xsns01,
#endif

#ifdef XSNS_02
  &Xsns02,
#endif

#ifdef XSNS_03
  &Xsns03,
#endif

#ifdef XSNS_04
  &Xsns04,
#endif

#ifdef XSNS_05
  &Xsns05,
#endif

#ifdef XSNS_06
  &Xsns06,
#endif

#ifdef XSNS_07
  &Xsns07,
#endif

#ifdef XSNS_08
  &Xsns08,
#endif

#ifdef XSNS_09
  &Xsns09,
#endif

#ifdef XSNS_10
  &Xsns10,
#endif

#ifdef XSNS_11
  &Xsns11,
#endif

#ifdef XSNS_12
  &Xsns12,
#endif

#ifdef XSNS_13
  &Xsns13,
#endif

#ifdef XSNS_14
  &Xsns14,
#endif

#ifdef XSNS_15
  &Xsns15,
#endif

#ifdef XSNS_16
  &Xsns16
#endif
};

const uint8_t xsns_present = sizeof(xsns_func_ptr) / sizeof(xsns_func_ptr[0]);  // Number of External Sensors found
uint8_t xsns_index = 0;

/*********************************************************************************************\
 * Function call to all xsns
 *
 * FUNC_JSON
 * FUNC_EVERY_SECOND
 * FUNC_EVERY_500MSECOND
 * FUNC_EVERY_100MSECOND
 * FUNC_EVERY_50_MSECOND
\*********************************************************************************************/

uint8_t XsnsPresent()
{
  return xsns_present;
}

boolean XsnsNextCall(byte Function)
{
  xsns_index++;
  if (xsns_index == xsns_present) xsns_index = 0;
  return xsns_func_ptr[xsns_index](Function);
}

