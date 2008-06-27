/*
    ChibiOS/RT - Copyright (C) 2006-2007 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ch.h>

#include "lpc214x.h"

/*
 * VIC Initialization.
 * NOTE: Better reset everything in the VIC, it is a HUGE source of trouble.
 */
void InitVIC(void) {
  int i;

  VIC *vic = VICBase;
  vic->VIC_IntSelect = 0;               /* All sources assigned to IRQ. */
  vic->VIC_SoftIntClear = ALLINTMASK;   /* No interrupts enforced */
  vic->VIC_IntEnClear = ALLINTMASK;     /* All sources disabled. */
  for (i = 0; i < 16; i++) {
    vic->VIC_VectCntls[i] = 0;
    vic->VIC_VectAddrs[i] = 0;
    vic->VIC_VectAddr = 0;
  }
}

/*
 * Set a vector for an interrupt source, the vector is enabled too.
 */
void SetVICVector(void *handler, int vector, int source) {

  VIC *vicp = VICBase;
  vicp->VIC_VectAddrs[vector] = (IOREG32)handler;
  vicp->VIC_VectCntls[vector] = (IOREG32)(source | 0x20);
}
