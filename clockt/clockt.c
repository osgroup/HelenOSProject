/*
 * Copyright (c) 2012 Petr Koupy
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @addtogroup clock
 * @{
 */

/*
 Modified by Mallika ,Suvadra,Suhani ,Rishu 
 *@file
 */


#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <io/pixel.h>
#include <task.h>
#include <str.h>
#include <window.h>
#include <grid.h>
#include <button.h>
#include <label.h>
#include <ctype.h>
#include <stdlib.h>
#include <str.h>
#include<errno.h>
#include "../tester/tester.h"

typedef struct my_label {
	label_t label;	
} my_label_t;

static void deinit_my_label(my_label_t *lbl)
{
	deinit_label(&lbl->label);
}

static void my_label_destroy(widget_t *widget)
{
	my_label_t *lbl = (my_label_t *) widget;

	deinit_my_label(lbl);

	free(lbl);
}
static bool init_my_label(my_label_t *lbl, widget_t *parent,
    const char *caption, uint16_t points, pixel_t background, pixel_t foreground)
{
	bool initialized = init_label(
	    &lbl->label, parent, caption, points, background, foreground);
	lbl->label.widget.destroy = my_label_destroy;
	return initialized;
}

static my_label_t *create_my_label(widget_t *parent,
    const char *caption, uint16_t points, pixel_t background, pixel_t foreground)
{
	my_label_t *lbl = (my_label_t *) malloc(sizeof(my_label_t));
	if (!lbl) {
		return NULL;
	}

	if (init_my_label(lbl, parent, caption, points, background, foreground)) {
		return lbl;
	} else {
		free(lbl);
		return NULL;
	}
}

static int toInteger1( const char *c ) {
	int value = 0;
	while ( isdigit( *c ) ) 
	{
		value *= 10;
		value += (int) (*c-'0');
		c++;
	}
	return value;
}

int main(int argc, char *argv[])
{
char buffer[30];
struct timeval tv;
struct tm result;
window_t *main_window = window_open(argv[1], true, true," ",0,720);
	if (!main_window) {
	printf("Cannot open main window.\n");
		return 1;
	}

	time_t curtime;
	gettimeofday(&tv, NULL); 
	curtime=tv.tv_sec;
	time_utc2tm(curtime,&result);
	strftime(buffer,30,"%T %m-%d-%Y",&result);

	pixel_t grd_bg = PIXEL(255, 25, 25, 112);
	
	pixel_t lbl_bg = PIXEL(255, 25, 25, 112);//(255, 240, 240, 240);
	pixel_t lbl_fg = PIXEL(255, 255, 255, 255);

	my_label_t *stime= create_my_label(NULL,buffer, 16, lbl_bg, lbl_fg);

	grid_t *grid = create_grid(window_root(main_window),1, 10, grd_bg);
	grid->add(grid, &stime->label.widget, 0, 7, 1, 2);
	window_resize(main_window,1024,60);
	window_exec(main_window);

	while(1){
		gettimeofday(&tv, NULL); 
		curtime=tv.tv_sec;
		time_utc2tm(curtime,&result);

//Converting month to integer		
		char month[5];
		strftime(month,5,"%m",&result);
		char *mon;
		mon=month;
		int value=0;
		value=toInteger1(mon);

		switch(value){
case 0:
			strftime(buffer,30,"%T Jan-%d, %Y",&result);		
			break;
case 1:
			strftime(buffer,30,"%T Feb-%d, %Y",&result);		
			break;
case 2:
			strftime(buffer,30,"%T Mar-%d, %Y",&result);		
			break;
case 3:
			strftime(buffer,30,"%T Apr-%d, %Y",&result);		
			break;
case 4:
			strftime(buffer,30,"%T May-%d, %Y",&result);		
			break;
case 5:
			strftime(buffer,30,"%T Jun-%d, %Y",&result);		
			break;
case 6:
			strftime(buffer,30,"%T Jul-%d, %Y",&result);		
			break;
case 7:
			strftime(buffer,30,"%T Aug-%d, %Y",&result);		
			break;
case 8:
			strftime(buffer,30,"%T Sep-%d, %Y",&result);		
			break;
case 9:
			strftime(buffer,30,"%T Oct-%d, %Y",&result);		
			break;
case 10:
			strftime(buffer,30,"%T Nov-%d, %Y",&result);		
			break;
case 11:
			strftime(buffer,30,"%T Dec-%d, %Y",&result);		
			break;
		}	
		stime->label.rewrite(&stime->label.widget, (void *)buffer);
	}

	task_retval(0);
	async_manager();

return 0;
}
