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

/** @addtogroup vlaunch
 * @{
 */

/*
 Modified by Mallika ,Suvadra,Suhani ,Rishu 
 *@file
 */

#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <io/pixel.h>
#include <task.h>
#include <str.h>
#include <str_error.h>
#include <window.h>
#include <grid.h>
#include <button.h>
#include <label.h>
#include <canvas.h>
#include <surface.h>
#include <source.h>
#include <drawctx.h>
#include <codec/tga.h>
#include "images.h"
#define LOGO_WIDTH   1024
#define LOGO_HEIGHT  720

#define NAME "vlaunch"

static char *winreg = NULL;

static int app_launch(const char *app)
{
	int rc;
	printf("%s: Spawning %s %s \n", NAME, app, winreg);

	task_id_t id;
	task_exit_t texit;
	int retval;
	rc = task_spawnl(&id, app, app, winreg, NULL);
	if (rc != EOK) {
		printf("%s: Error spawning %s %s (%s)\n", NAME, app,
		    winreg, str_error(rc));
		return -1;
	}
	rc = task_wait(id, &texit, &retval);
	if (rc != EOK || texit != TASK_EXIT_NORMAL) {
		printf("%s: Error retrieving retval from %s (%s)\n", NAME,
		    app, str_error(rc));
		return -1;
	}

	return retval;
}
static int app_launchs(const char *app)
{
	int rc;
	printf("%s: Spawning %s %s \n", NAME, app, winreg);

	task_id_t id;
	task_exit_t texit;
	int retval;
	rc = task_spawnl(&id, app, app,"/", NULL);
	if (rc != EOK) {
		printf("%s: Error spawning %s %s (%s)\n", NAME, app,
		    winreg,str_error(rc));
		return -1;
	}
	rc = task_wait(id, &texit, &retval);
	if (rc != EOK || texit != TASK_EXIT_NORMAL) {
		printf("%s: Error retrieving retval from %s (%s)\n", NAME,
		    app, str_error(rc));
		return -1;
	}

	return retval;
}

// To open the different applications
static void on_vterm(widget_t *widget, void *data)
{
	app_launch("/app/vterm");
}



static void on_explorer(widget_t *widget, void *data)
{
	app_launchs("/app/fileexplorer");
}

static void on_calendar(widget_t *widget, void *data)
{
	app_launch("/app/calendar");
}

static void on_calculator(widget_t *widget, void *data)
{
	app_launch("/app/calculator");
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Compositor server not specified.\n");
		return 1;
	}
	
	surface_t *logo = decode_tga((void *) w2_tga, w2_tga_size, 0);
        if (!logo) {
                printf("Unable to decode logo.\n");
                return 1;
        }

	winreg = argv[1];
	window_t *main_window = window_open(argv[1], true, true,"Desktop", 0, 0);
	if (!main_window) {
		printf("Cannot open main window.\n");
		return 1;
	}
		pixel_t grd_bg = PIXEL(255, 60, 20, 0);//(255, 0, 240, 0);//(30,60, 20, 20);
		pixel_t btn_bg = PIXEL(255, 240, 240, 240);
		pixel_t btn_fg = PIXEL(255, 0, 0, 0);
		
	canvas_t *logo_canvas = create_canvas(NULL, LOGO_WIDTH, LOGO_HEIGHT,
            logo);
	button_t *btn_vterm = create_button(NULL, "V-Term", 16, btn_bg,
	    btn_fg);
	button_t *btn_calculator = create_button(NULL, "X-Calc", 16, btn_bg,
	    btn_fg);
	button_t *btn_calendar = create_button(NULL, "X-Calendar", 16, btn_bg,
	    btn_fg);
	button_t *btn_explorer = create_button(NULL, "File Explorer", 16, btn_bg,
	    btn_fg);
	

	grid_t *grid = create_grid(window_root(main_window), 25, 25, grd_bg);
	
	if ( !btn_vterm || !btn_calculator || !btn_calendar || !btn_explorer  || !grid) {
		window_close(main_window);
		printf("Cannot create widgets.\n");
		return 1;
	}
	
	sig_connect(&btn_vterm->clicked, NULL, on_vterm);
	sig_connect(&btn_calculator->clicked, NULL, on_calculator);
	sig_connect(&btn_calendar->clicked, NULL, on_calendar);
	sig_connect(&btn_explorer->clicked, NULL, on_explorer);
	
	grid->add(grid, &logo_canvas->widget, 0, 0, 20, 24);
	grid->add(grid, &btn_vterm->widget, 21, 5, 2, 2);
	grid->add(grid, &btn_calculator->widget, 21, 8, 2, 2);
	grid->add(grid, &btn_calendar->widget,21, 12, 2, 2);
	grid->add(grid, &btn_explorer->widget, 21, 15, 2, 2);
	
	
	window_resize(main_window,50+LOGO_WIDTH,LOGO_HEIGHT);
	window_exec(main_window);
	task_retval(0);
	async_manager();
	
	return 0;
}

/** @}
 */
