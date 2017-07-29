/*
 * Copyright (C) siying
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file "modules/guidance_h_module/guidance_h_module.h"
 * @author siying
 * Logic for MODULE
 */

#ifndef GUIDANCE_H_MODULE_H
#define GUIDANCE_H_MODULE_H


extern void guidance_h_module_init(void);
extern void guidance_h_module_run(bool in_flight);
extern void guidance_h_module_enter(void);
extern void guidance_h_module_read_rc(void);

#endif

