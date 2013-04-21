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

/** @addtogroup file explorer
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
	#include <unistd.h>
	#include <dirent.h>
	#include <fcntl.h>
	#include <getopt.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sort.h>
	
	#define LS_BOGUS 0
	#define LS_FILE  1
	#define LS_DIR   2
	
	
	struct dir_elem_t {
		char *name;
		struct stat s;
	};
	
	static signed int ls_scan_dir(const char *d, DIR *dirp, struct dir_elem_t **dir_list_ptr );
	static char *winreg = NULL;
	static char *arr[30];
	static window_t *main_window;
	static grid_t *grid;	
	
	static int app_launch(const char *app,char * ap)
	{
		int rc;
		//printf(" Spawning %s %s \n", app, winreg);
	
		task_id_t id;
		task_exit_t texit;
		int retval;
		rc = task_spawnl(&id, app, app,ap, NULL);
		if (rc != EOK) {
			printf("%s: Error spawning %s (%s)\n",  app,
			    winreg, str_error(rc));
			return -1;
		}
		rc = task_wait(id, &texit, &retval);
		if (rc != EOK || texit != TASK_EXIT_NORMAL) {
			printf("Error retrieving retval from %s (%s)\n", app, str_error(rc));
			return -1;
		}
	
		return retval;
	}
	
	static int on_file(char * ap)
	{
		int rc;
		//printf(" Spawning %s %s \n", app, winreg);
		char *app;
			
		app=str_dup("/app/edit");
		task_id_t id;
		task_exit_t texit;
		int retval;
		rc = task_spawnl(&id, app, app,ap, NULL);
		if (rc != EOK) {
			printf("%s: Error spawning (%s)\n",  app,
			    str_error(rc));
			return -1;
		}
		rc = task_wait(id, &texit, &retval);
		if (rc != EOK || texit != TASK_EXIT_NORMAL) {
			printf("Error retrieving retval from %s (%s)\n", app, str_error(rc));
			return -1;
		}
		return retval;
	}
	
	static unsigned int ls_scope(const char *path, struct dir_elem_t *de)
	{
		if (stat(path, &de->s))
			return LS_BOGUS;
		if (de->s.is_file)
			return LS_FILE;
		else if (de->s.is_directory)
			return LS_DIR;
	
		return LS_BOGUS;
	}	
	
	
	/*static int on_button(grid_t *grid ,window_t *ab,char *app)
	{
		//printf("%s\n",app);
		//app_launch("/app/fileexplorer",app);
		int alloc_blocks = 20;
		int nbdirs = 0;
		int rc;
		int len;
		char *buff;
		struct dir_elem_t *tmp;
		struct dir_elem_t *tosort;
		struct dirent *dp;
		struct dir_elem_t de;
		DIR *dirp;
		pixel_t btn_bg = PIXEL(255, 255, 255, 255);
		pixel_t btn_fg = PIXEL(200, 200, 200, 200);
		//grid_t *grid = create_grid(window_root(ab), 20, 2, grd_bg);
		button_t *btn[20]={NULL};
		de.name = (char *) malloc(50);
		str_cpy(de.name,10,app);
		int scope = ls_scope(de.name, &de);
		if(scope== LS_DIR){
		dirp = opendir(de.name);
			if (!dirp)
			return -1;
		buff = (char *) malloc(50);
		if (!buff) {
			//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
			return -1;
		}
		
		tosort = (struct dir_elem_t *) malloc(alloc_blocks * sizeof(*tosort));
		if (!tosort) {
			//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
			free(buff);
			return -1;
		}
		while ((dp = readdir(dirp))) {
			if (nbdirs + 1 > alloc_blocks) {
				alloc_blocks += alloc_blocks;
				tmp = (struct dir_elem_t *) realloc(tosort,
				alloc_blocks * sizeof(struct dir_elem_t));
				if (!tmp) {
					//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
					//goto out;
				}
				tosort = tmp;
			}
			
			 //fill the name field 
			tosort[nbdirs].name = (char *) malloc(str_size(dp->d_name) + 1);
			if (!tosort[nbdirs].name) {
				//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
			//	goto out;
			}
			str_cpy(tosort[nbdirs].name, str_size(dp->d_name) + 1, dp->d_name);
			len = snprintf(buff,49, "%s/%s", de.name, tosort[nbdirs].name);
			buff[len] = '\0';
			rc = stat(buff, &tosort[nbdirs++].s);
			if (rc != 0) {
			//	printf("ls: skipping bogus node %s\n", buff);
			//	printf("rc=%d\n", rc);
				//goto out;
			}
		
		}
		int l=0,k=0;
		if(nbdirs>20)
		  nbdirs=20;
		for (int i = 0; i <=nbdirs; i++)
		{
		
			if(k>=22)
			{
			l=l+3;
			k=0;
			}
		btn[i] = create_button(NULL,tosort[i].name, 16, btn_bg, btn_fg);
		grid->add(grid, &btn[i]->widget, l,k, 2, 2);
		k=k+3;
		}
		}
		
		
		
		return 1;
		
		
		
	}*/
	
	static void button0 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[0]);
	}	
	
	static void button1 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[1]);
	}
	static void button2 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[2]);
	}
	static void button3 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[3]);
	}
	static void button4 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[4]);
	}
	static void button5 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[5]);
	}
	static void button6 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[6]);
	}
	static void button7 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[7]);
	}
	
	static void button8 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[8]);
	}
	static void button9 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[9]);
	}
	static void button10(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[10]);
	}
	static void button11 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[11]);
	}
	static void button12(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[12]);
	}
	static void button13(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[13]);
	}
	static void button14 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[14]);
	}
	static void button15(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[15]);
	}
	
	static void button16(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[16]);
	}
	
	static void button17(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[17]);
	}
	
	static void button18(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[18]);
	}
	
	static void button19 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[19]);
	}
	
	static void button20(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[20]);
	}
	static void button21 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[21]);
	}
	static void button22(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[22]);
	}
	static void button23(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[23]);
	}
	static void button24 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[24]);
	}
	static void button25(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[25]);
	}
	
	static void button26(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[26]);
	}
	
	static void button27(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[27]);
	}
	
	static void button28(widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[28]);
	}
	
	static void button29 (widget_t *widget, void *data)
	{
	//on_button(grid,main_window,arr[0]);	
	app_launch("/app/fileexplorer",arr[29]);
	}
	
	
	static void backs (widget_t *widget, void *data)
	{
	window_close(main_window);
	}
	
	static signed int ls_scan_dir(const char *d, DIR *dirp, struct dir_elem_t **dir_list_ptr)
	{
		int alloc_blocks = 20;
		int nbdirs = 0;
		int rc;
		int len;
		char *buff;
		char *arg=str_dup("comp:0/winreg");
		struct dir_elem_t *tmp;
		struct dir_elem_t *tosort;
		struct dirent *dp;
		winreg = arg;
		int i;
		
		main_window = window_open(arg, true, true,"file explorer", 200,200);
		if (!main_window) 
			{
			printf("Cannot open main window.\n");
			return 1;
			}
	
		pixel_t grd_bg = PIXEL(0, 0, 0, 0);
		pixel_t btn_bg = PIXEL(255, 255, 255, 255);
		pixel_t btn_fg = PIXEL(255, 0, 0, 255);
		grid = create_grid(window_root(main_window), 30, 25, grd_bg);
		button_t *btn[30]={NULL};
		if (!dirp)
			return -1;
	
		buff = (char *) malloc(50);
		if (!buff) {
			//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
			return -1;
		}
		
		tosort = (struct dir_elem_t *) malloc(alloc_blocks * sizeof(*tosort));
		if (!tosort) {
			//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
			free(buff);
			return -1;
		}
		
		while ((dp = readdir(dirp))) {
			if (nbdirs + 1 > alloc_blocks) {
				alloc_blocks += alloc_blocks;
				tmp = (struct dir_elem_t *) realloc(tosort,
				alloc_blocks * sizeof(struct dir_elem_t));
				if (!tmp) {
					//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
					//goto out;
				}
				tosort = tmp;
			}
			
			/* fill the name field */
			tosort[nbdirs].name = (char *) malloc(str_size(dp->d_name) + 1);
			if (!tosort[nbdirs].name) {
				//cli_error(CL_ENOMEM, "ls: failed to scan %s", d);
			//	goto out;
			}
			str_cpy(tosort[nbdirs].name, str_size(dp->d_name) + 1, dp->d_name);
			len = snprintf(buff,49, "%s/%s", d, tosort[nbdirs].name);
			buff[len] = '\0';
			rc = stat(buff, &tosort[nbdirs++].s);
			if (rc != 0) {
			//	printf("ls: skipping bogus node %s\n", buff);
			//	printf("rc=%d\n", rc);
				//goto out;
			}
		
		}
		
		
		button_t *back=create_button(NULL,"back", 16, btn_bg, btn_fg);
		grid->add(grid, &back->widget, 0,0, 1, 3);
		int l=2,k=0;

		if(nbdirs==0)
		{
		window_resize(main_window,750,750);
		window_exec(main_window);
		task_retval(0);
		async_manager();
		return nbdirs;
		}
		if(nbdirs>30)
		  nbdirs=30;
		
		
		
		for ( i = 0; i < nbdirs; i++)
		{
		//printf("%d\n",nbdirs);
		arr[i]=malloc(sizeof(char)*20);
		str_cpy(arr[i],20,tosort[i].name);
		//printf("%s->%d\n",arr[i],i);
		}
		
		for ( i = 0; i <=nbdirs; i++)
		{
		
			if(k>=22){
			l=l+4;
			k=0;
			}
		btn[i] = create_button(NULL,tosort[i].name, 16, btn_bg, btn_fg);
		grid->add(grid, &btn[i]->widget, l,k, 3, 4);
		k=k+5;
		
		}
		//printf("started\n");
		sig_connect(&back->clicked,NULL,backs);
		sig_connect(&btn[0]->clicked, NULL,button0);
		sig_connect(&btn[1]->clicked, NULL,button1);
		sig_connect(&btn[2]->clicked, NULL,button2);
		sig_connect(&btn[3]->clicked, NULL,button3);
		sig_connect(&btn[4]->clicked, NULL,button4);
		sig_connect(&btn[5]->clicked, NULL,button5);
		sig_connect(&btn[6]->clicked, NULL,button6);
		sig_connect(&btn[7]->clicked, NULL,button7);
		sig_connect(&btn[8]->clicked, NULL,button8);
		sig_connect(&btn[9]->clicked, NULL,button9);
		sig_connect(&btn[10]->clicked, NULL,button10);
		sig_connect(&btn[11]->clicked, NULL,button11);
		sig_connect(&btn[12]->clicked, NULL,button12);
		sig_connect(&btn[13]->clicked, NULL,button13);
		sig_connect(&btn[14]->clicked, NULL,button14);
		sig_connect(&btn[15]->clicked, NULL,button15);
		sig_connect(&btn[16]->clicked, NULL,button16);
		sig_connect(&btn[17]->clicked, NULL,button17);
		sig_connect(&btn[18]->clicked, NULL,button18);
		sig_connect(&btn[19]->clicked, NULL,button19);
		sig_connect(&btn[20]->clicked, NULL,button20);
		sig_connect(&btn[21]->clicked, NULL,button21);
		sig_connect(&btn[22]->clicked, NULL,button22);
		sig_connect(&btn[23]->clicked, NULL,button23);
		sig_connect(&btn[24]->clicked, NULL,button24);
		sig_connect(&btn[25]->clicked, NULL,button25);
		sig_connect(&btn[26]->clicked, NULL,button26);
		sig_connect(&btn[27]->clicked, NULL,button27);
		sig_connect(&btn[28]->clicked, NULL,button28);
		sig_connect(&btn[29]->clicked, NULL,button29);
		//printf("ended\n");*/
		window_resize(main_window,750,750);
		window_exec(main_window);
		task_retval(0);
		async_manager();
		return nbdirs;
		}
	
	
	
	
	int main(int argc, char *argv[])
	{
		
		struct dir_elem_t de;
		DIR *dirp;
		
		unsigned int scope;
		if (argc < 2) {
			printf("Invalid number of arguments\n");
			return 1;
		}
		de.name=(char*)malloc(50);
		str_cpy(de.name,10,argv[1]);
		scope = ls_scope(de.name, &de);
		switch (scope)
		{
			case LS_FILE:
				on_file(de.name);
				break;
			case LS_DIR:
				dirp = opendir(de.name);
				if (!dirp)
				 {
				return 1;
				}
			
			ls_scan_dir(de.name, dirp, NULL);
			closedir(dirp);
			break;
			
			}
		return 0;
		
	}
	
	
