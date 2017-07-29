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
 * @file "modules/count_time/count_time.h"
 * @author siying
 * Counts the time
 */

#ifndef COUNT_TIME_H
#define COUNT_TIME_H

extern void count_time(void);
extern void reset_time(int num);
extern float time_temp1;
extern float time_temp2;
extern int counter_temp1;
extern int counter_temp2;


#endif

