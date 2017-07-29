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
 * @file "modules/count_time/count_time.c"
 * @author siying
 * Counts the time
 */

#include "modules/count_time/count_time.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef FREQ
#define FREQ 100.0
#endif // FREQ



int counter_temp1 = 0;
int counter_temp2 = 0;
float time_temp1, time_temp2;

 void count_time() {
    counter_temp1++;
    counter_temp2++;
    //printf("Count = %d\n", counter_temp);
    time_temp1 = counter_temp1/100.0;
    time_temp2 = counter_temp2/100.0;
}


 void reset_time(int num){
	 switch(num){
	 case 1:
		 counter_temp1 = 0;
		 time_temp1 = 0.0;
		 break;
	 case 2:
		 counter_temp2 = 0;
		 time_temp2 = 0.0;
		 break;
	 }
 }


