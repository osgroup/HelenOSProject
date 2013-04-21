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

/** @addtogroup calendar
 * @{
 */

/*
 Modified by Mallika ,Suvadra,Suhani ,Rishu 
 *@file
 */
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <io/pixel.h>
#include <task.h>
#include <window.h>
#include <grid.h>
#include <button.h>
#include <label.h>
#include <ctype.h>
#include <stdlib.h>
#include <str.h>
#include<errno.h>
#include "../tester/tester.h"

int day=0,month=0,year=0,flagRead=0,newday=0;

typedef struct x_label {
				label_t label;
			} x_label_t;

static void deinit_x_label(x_label_t *lbl)
			{
				deinit_label(&lbl->label);
			}
			
static void x_label_destroy(widget_t *widget)
			{
				x_label_t *lbl = (x_label_t *) widget;
				deinit_x_label(lbl);
				free(lbl);
			}
			
static bool init_x_label(x_label_t *lbl, widget_t *parent,
				const char *caption, uint16_t points, pixel_t background, pixel_t foreground)
			{
				bool initialized = init_label(&lbl->label, parent, caption, points, background, foreground);
				lbl->label.widget.destroy = x_label_destroy;
				return initialized;
			}
			
			static x_label_t *create_x_label(widget_t *parent,
				const char *caption, uint16_t points, pixel_t background, pixel_t foreground)
			{
				x_label_t *lbl = (x_label_t *) malloc(sizeof(x_label_t));
				if (!lbl) {
					return NULL;
				}
			
				if (init_x_label(lbl, parent, caption, points, background, foreground)) {
					return lbl;
				} 
				else {
					free(lbl);
					return NULL;
				}
			}		

static int toInteger( const char *c ) {
	int value = 0;
	while ( isdigit( *c ) ) 
	{
		value *= 10;
		value += (int) (*c-'0');
		c++;
	}
	return value;
}

static void fileOp(void)
{
   char line[10];
   char *date;

   FILE *fp;
   const char *filename= "/testCalendar";
   fp = fopen(filename,"rt"); // read mode
   if(fp == NULL)
   {
      printf("Error while opening the file.\n");
   }
   else{

	while(fgets(line,sizeof(line),fp) != NULL){ 
	
		date=line;
		
		if(flagRead==0)
			{day=toInteger(date); flagRead++;
			newday=day;}
		else if(flagRead==1)
			{month=toInteger(date); flagRead++;}
		else if(flagRead==2)
			{year=toInteger(date);}
	}
	fclose(fp);
  }
}

int main(int argc, char *argv[])
{

//reading from file
fileOp();

int cal_year;
int total_odd_days,TOTAL,od1=0,od2=0,fod;
int leap_years,ordinary_years;
int flag=1;
cal_year=year-1;

while(flag)
{
	if(cal_year>=400){
		cal_year=cal_year-400;
				if(cal_year==0){
					total_odd_days=0;
					flag=0;
					}
			}
	else
		{	
		if(cal_year>=100){
				cal_year=cal_year-100;
					od1=od1+5;
			}
		else{
			leap_years=cal_year/4;
			ordinary_years=cal_year-leap_years;
			od2=leap_years*2+ordinary_years*1;
			total_odd_days=od1+od2;
			total_odd_days=total_odd_days%7;
			flag=0;
			}
		}	
}
if(year%400 ==0 || (year%100 != 0 && year%4 == 0))
	{
		if(month==1){
			TOTAL=day%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==2){
			TOTAL=(31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==3){
			TOTAL=(31+29+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==4){
			TOTAL=(31+29+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==5){
			TOTAL=(31+29+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==6){
			TOTAL=(31+29+31+30+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==7){
			TOTAL=(31+29+31+30+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month== 8){
			TOTAL=(31+29+31+30+31+30+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month== 9){
			TOTAL=(31+29+31+30+31+30+31+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month== 10){
			TOTAL=(31+29+31+30+31+30+31+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month== 11){
			TOTAL=(31+29+31+30+31+30+31+31+30+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month== 12){
			TOTAL=(31+29+31+30+31+30+31+31+30+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
	}
else{
	if(month==1){
			TOTAL=day%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==2){
			TOTAL=(31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==3){
			TOTAL=(31+28+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==4){
			TOTAL=(31+28+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==5){
			TOTAL=(31+28+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==6){
			TOTAL=(31+28+31+30+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==7){
			TOTAL=(31+28+31+30+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==8){
			TOTAL=(31+28+31+30+31+30+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==9){
			TOTAL=(31+28+31+30+31+30+31+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==10){
			TOTAL=(31+28+31+30+31+30+31+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==11){
			TOTAL=(31+28+31+30+31+30+31+31+30+31+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}
		if(month==12){
			TOTAL=(31+28+31+30+31+30+31+31+30+31+30+day)%7;
			fod=TOTAL+total_odd_days;
			fod=fod%7;
		}	
	}
int firstdayofyear=(total_odd_days+1)%7;
int wk=0;
 if(year%400 ==0 || (year%100 != 0 && year%4 == 0)){
switch (firstdayofyear){
                case 0:
                {
                        if(month==1){
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==3){
					day=day+31+29;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==4){
					day=day+31+29+31;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==5){
					day=day+31+29+31+30;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==6){
					day=day+31+29+31+30+31;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==7){
					day=day+31+29+31+30+31+30;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==8){
					day=day+31+29+31+30+31+30+31;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==9){
					day=day+31+29+31+30+31+30+31+31;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==10){
					day=day+31+29+31+30+31+30+31+31+30;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==11){
					day=day+31+29+31+30+31+30+31+31+30+31;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==12){
					day=day+31+29+31+30+31+30+31+31+30+31+30;
					if(day%7==0)
						wk=day/7;
					else{
						wk=day/7;
						wk++;
					    }
					}				
                        break;
                }
                case 1:
                {
			if(month==1){
					if(day%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==0){
						wk=day/7;
						wk++;}
					else {
						wk=(day)/7;
						wk++;
					    }
					}
			if(month==3){
					day=day+31+29;
					if(day%7==0){
						wk=day/7;
						wk++;}
					else  {
						wk=day/7;
						wk++;
					    }
					}
			if(month==4){
					day=day+31+29+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==5){
					day=day+31+29+31+30;
					if(day%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==6){
					day=day+31+29+31+30+31;
					if(day%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==7){
					day=day+31+29+31+30+31+30;
					if(day%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==8){
					day=day+31+29+31+30+31+30+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==9){
					day=day+31+29+31+30+31+30+31+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==10){
					day=day+31+29+31+30+31+30+31+31+30;
					if((day)%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==11){
					day=day+31+29+31+30+31+30+31+31+30+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==12){
					day=day+31+29+31+30+31+30+31+31+30+31+30;
					if((day)%7==0){
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}	
                        break;
                }
                case 2:
                {
			if(month==1){
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else {
						wk=(day)/7;
						wk++;
					    }
					}
			if(month==3){
					day=day+31+29;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else  {
						wk=day/7;
						wk++;
					    }
					}
			if(month==4){
					day=day+31+29+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==5){
					day=day+31+29+31+30;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==6){
					day=day+31+29+31+30+31;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==7){
					day=day+31+29+31+30+31+30;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==8){
					day=day+31+29+31+30+31+30+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==9){
					day=day+31+29+31+30+31+30+31+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==10){
					day=day+31+29+31+30+31+30+31+31+30;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==11){
					day=day+31+29+31+30+31+30+31+31+30+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==12){
					day=day+31+29+31+30+31+30+31+31+30+31+30;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
                        break;
                }
                case 3:
                {
         
			if(month==1){
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			
				if(month==2){
					day=day+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==3){
					day=day+31+29;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==4){
					day=day+31+29+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				
				if(month==5){
					day=day+31+29+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==6){
					day=day+31+29+31+30+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==7){
					day=day+31+29+31+30+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==8){
					day=day+31+29+31+30+31+30+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==9){
					day=day+31+29+31+30+31+30+31+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==10){
					day=day+31+29+31+30+31+30+31+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==11){
					day=day+31+29+31+30+31+30+31+31+30+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==12){
					day=day+31+29+31+30+31+30+31+31+30+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}

                        break;
                }
                case 4:
                {		
			if(month==1){
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
					       else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==3){
					day=day+31+29;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==4){
					day=day+31+29+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==5){
					day=day+31+29+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==6){
					day=day+31+29+31+30+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==7){
					day=day+31+29+31+30+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==8){
					day=day+31+29+31+30+31+30+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==9){
					day=day+31+29+31+30+31+30+31+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==10){
					day=day+31+29+31+30+31+30+31+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==11){
					day=day+31+29+31+30+31+30+31+31+30+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==12){
					day=day+31+29+31+30+31+30+31+31+30+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
                        break;
                }
                case 5:
                {
				if(month==1){
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
						
					}
				if(month==2){
					day=day+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
					}
			if(month==3){
					day=day+31+29;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==4){
					day=day+31+29+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==5){
					day=day+31+29+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==6){
					day=day+31+29+31+30+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==7){
					day=day+31+29+31+30+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==8){
					day=day+31+29+31+30+31+30+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==9){
					day=day+31+29+31+30+31+30+31+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==10){
					day=day+31+29+31+30+31+30+31+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==11){
					day=day+31+29+31+30+31+30+31+31+30+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==12){
					day=day+31+29+31+30+31+30+31+31+30+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {                               
						wk=day/7;
						wk=wk+2;
					}
					}
				
                        break;
                }
                case 6:
                {
      
	if(month==1){
			if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
						
					}
				if(month==2){
					day=day+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
					}
			if(month==3){
					day=day+31+29;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==4){
					day=day+31+29+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==5){
					day=day+31+29+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==6){
					day=day+31+29+31+30+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==7){
					day=day+31+29+31+30+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==8){
					day=day+31+29+31+30+31+30+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==9){
					day=day+31+29+31+30+31+30+31+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==10){
					day=day+31+29+31+30+31+30+31+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==11){
					day=day+31+29+31+30+31+30+31+31+30+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==12){
					day=day+31+29+31+30+31+30+31+31+30+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {                          
						wk=day/7;
						wk=wk+2;
					}
					}
                        break;
                }
                default:
                {
                        puts("Day of year : Wrong Date!");
                }
        }
	
}
else{
switch (firstdayofyear)                                    /////////////////////  leap year situation//////////////
        {
                case 0:
                {

			   if(month==1){
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==3){
					day=day+31+28;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==4){
					day=day+31+28+31;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==5){
					day=day+31+28+31+30;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==6){
					day=day+31+28+31+30+31;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==7){
					day=day+31+28+31+30+31+30;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==8){
					day=day+31+28+31+30+31+30+31;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==9){
					day=day+31+28+31+30+31+30+31+31;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==10){
					day=day+31+28+31+30+31+30+31+31+30;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==11){
					day=day+31+28+31+30+31+30+31+31+30+31;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==12){
					day=day+31+28+31+30+31+30+31+31+30+31+30;
					if(day%7==0)
						wk=day/7;
			
					else{
						wk=day/7;
						wk++;
					    }
					}				
                        break;
                }
              case 1:
                {
			if(month==1){
					if(day%7==0){
						wk=day/7;
						wk++;}
						
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==0){
						wk=day/7;
						wk++;}
			
					else {
						wk=(day)/7;
						wk++;
					    }
					}
			if(month==3){
					day=day+31+28;
					if(day%7==0){
						wk=day/7;
						wk++;}
			
					else  {
						wk=day/7;
						wk++;
					    }
					}
			if(month==4){
					day=day+31+28+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==5){
					day=day+31+28+31+30;
					if(day%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==6){
					day=day+31+28+31+30+31;
					if(day%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==7){
					day=day+31+28+31+30+31+30;
					if(day%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==8){
					day=day+31+28+31+30+31+30+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==9){
					day=day+31+28+31+30+31+30+31+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==10){
					day=day+31+28+31+30+31+30+31+31+30;
					if((day)%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==11){
					day=day+31+28+31+30+31+30+31+31+30+31;
					if((day)%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==12){
					day=day+31+28+31+30+31+30+31+31+30+31+30;
					if((day)%7==0){
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}	
                        break;
                }
                case 2:
                {
			if(month==1){
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
						
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else {
						wk=(day)/7;
						wk++;
					    }
					}
			if(month==3){
					day=day+31+28;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else  {
						wk=day/7;
						wk++;
					    }
					}
			if(month==4){
					day=day+31+28+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==5){
					day=day+31+28+31+30;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==6){
					day=day+31+28+31+30+31;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==7){
					day=day+31+28+31+30+31+30;
					if(day%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==8){
					day=day+31+28+31+30+31+30+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==9){
					day=day+31+28+31+30+31+30+31+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==10){
					day=day+31+28+31+30+31+30+31+31+30;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==11){
					day=day+31+28+31+30+31+30+31+31+30+31;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
			if(month==12){
					day=day+31+28+31+30+31+30+31+31+30+31+30;
					if((day)%7==6){
						day=day+1;
						wk=day/7;
						wk++;}
			
					else{
						wk=day/7;
						wk++;
					    }
					}
                        break;
                }
                case 3:
                {
                       if(month==1){
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			
				if(month==2){
					day=day+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==3){
					day=day+31+28;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==4){
					day=day+31+28+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				
				if(month==5){
					day=day+31+28+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==6){
					day=day+31+28+31+30+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==7){
					day=day+31+28+31+30+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==8){
					day=day+31+28+31+30+31+30+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==9){
					day=day+31+28+31+30+31+30+31+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==10){
					day=day+31+28+31+30+31+30+31+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==11){
					day=day+31+28+31+30+31+30+31+31+30+31;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==12){
					day=day+31+28+31+30+31+30+31+31+30+31+30;
					if(day%7==5){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}

                        break;
                }
                case 4:
                {
			if(month==1){
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
					       else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==2){
					day=day+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==3){
					day=day+31+28;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==4){
					day=day+31+28+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==5){
					day=day+31+28+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==6){
					day=day+31+28+31+30+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==7){
					day=day+31+28+31+30+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==8){
					day=day+31+28+31+30+31+30+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==9){
					day=day+31+28+31+30+31+30+31+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==10){
					day=day+31+28+31+30+31+30+31+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
				if(month==11){
					day=day+31+28+31+30+31+30+31+31+30+31;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
			if(month==12){
					day=day+31+28+31+30+31+30+31+31+30+31+30;
					if(day%7==4){
						wk=day/7;
						wk=wk+2;
						}
						
					else{   
						if(day%7==5){
						wk=day/7;
						wk=wk+2;}
						else if(day%7==6){
						wk=day/7;
						wk=wk+2;}
						else {
								wk=day/7;
								wk++;
							}
					    }
					}
                        break;
                }
                case 5:
                {
				if(month==1){
					
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
						
					}
				if(month==2){
					day=day+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
					}
			if(month==3){
					day=day+31+28;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==4){
					day=day+31+28+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==5){
					day=day+31+28+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==6){
					day=day+31+28+31+30+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==7){
					day=day+31+28+31+30+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==8){
					day=day+31+28+31+30+31+30+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==9){
					day=day+31+28+31+30+31+30+31+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==10){
					day=day+31+28+31+30+31+30+31+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==11){
					day=day+31+28+31+30+31+30+31+31+30+31;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==12){
					day=day+31+28+31+30+31+30+31+31+30+31+30;
					if((day%7==0)||(day%7==1)){
						wk=day/7;
						wk++;}
					else {                               
						wk=day/7;
						wk=wk+2;
					}
					}
				
                        break;
                }
                case 6:
                {

		if(month==1){
			if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
						
					}
				if(month==2){
					day=day+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;}
					}
			if(month==3){
					day=day+31+28;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==4){
					day=day+31+28+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==5){
					day=day+31+28+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==6){
					day=day+31+28+31+30+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==7){
					day=day+31+28+31+30+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==8){
					day=day+31+28+31+30+31+30+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==9){
					day=day+31+28+31+30+31+30+31+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==10){
					day=day+31+28+31+30+31+30+31+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
				if(month==11){
					day=day+31+28+31+30+31+30+31+31+30+31;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {
						wk=day/7;
						wk=wk+2;
					}
					}
			if(month==12){
					day=day+31+28+31+30+31+30+31+31+30+31+30;
					if((day%7==1)){
						wk=day/7;
						wk++;}
					else {                              
						wk=day/7;
						wk=wk+2;
					}
					}
                        break;
                }
                default:
                {
                        puts("Day of year : Wrong Date!");
                }
        }
}


char dayofWeek[10];
char *DOW;
char* weekNumber=(char *)malloc(sizeof(char)*10);									
snprintf(weekNumber,8,"%d",wk);

if(fod==0)
	str_cpy(dayofWeek,7,"SUNDAY");
else if(fod==1)
	str_cpy(dayofWeek,7,"MONDAY");
else if(fod==2)
	str_cpy(dayofWeek,8,"TUESDAY");
else if(fod==3)
	str_cpy(dayofWeek,10,"WEDNESDAY");
else if(fod==4)
	str_cpy(dayofWeek,9,"THURSDAY");
else if(fod==5)
	str_cpy(dayofWeek,7,"FRIDAY");
else if(fod==6)
	str_cpy(dayofWeek,9,"SATURDAY");
DOW=dayofWeek;

//printf("\nday of week: %s\nweek of year:%s\n",DOW,weekNumber);


if (argc >= 2) {
					window_t *main_window = window_open(argv[1], true, true, "X-Calendar", 255, 240);
					if (!main_window) {
						printf("Cannot open main window.\n");
						return 1;
					}
			
					pixel_t grd_bg = PIXEL(255, 240, 240, 240);
					pixel_t lbl_bg = PIXEL(255,240, 240, 240);
					pixel_t lbl_fg = PIXEL(255, 0, 0, 0);
					
					char *dates,*months,*years,*dash;
					dash=str_dup("-");
					dates=(char*)malloc(sizeof(char)*8);
					months=(char *)malloc(sizeof(char)*8);
					years=(char *)malloc(sizeof(char)*8);
					printf("%d,%d,%d->is day\n",day,month,year);
					snprintf(dates,25, "%d", newday);
					snprintf(months,9,"%d",month);
					printf("%s->months\n",months);
					snprintf(years,9,"%d",year);
					printf("years:%s",years);
					str_append(dates,9,dash);
					printf("dates:%s\n",dates);
					str_append(dates,9,months);
					printf("dates:%s\n",dates);
					str_append(dates,9,dash);
					str_append(dates,12,years);
					printf("dates:%s\n",dates);
					printf("%s\n",dates);
					//label_t *lbl_caption = create_label(NULL,"Calendar App", 16, lbl_bg, lbl_fg);
					grid_t *grid = create_grid(window_root(main_window),6, 6, grd_bg);
					x_label_t *lbl_display1 = create_x_label(NULL, "DATE :", 16, lbl_bg, lbl_fg);		
			        x_label_t *lbl_display2 = create_x_label(NULL, "DAY OF WEEK:", 16, lbl_bg, lbl_fg);	
			        x_label_t *lbl_display3 = create_x_label(NULL, "WEEK OF YEAR:", 16, lbl_bg, lbl_fg);	
			        
			        x_label_t *lbl_dayofweek = create_x_label(NULL, DOW, 16, lbl_bg, lbl_fg);	
			        x_label_t *lbl_weekofyear = create_x_label(NULL, weekNumber, 16, lbl_bg, lbl_fg);	
			        x_label_t *lbl_datefromfile = create_x_label(NULL,dates, 16, lbl_bg, lbl_fg);
			        
					if (!lbl_display1 || !lbl_display2 || !lbl_display3 || !lbl_dayofweek 
								|| !lbl_weekofyear || !lbl_datefromfile || !grid) 
					{
						window_close(main_window);
						printf("Cannot create widgets.\n");
						return 1;
					}
	
//					grid->add(grid, &lbl_caption->widget, 0, 0, 1, 2);
					grid->add(grid, &lbl_display1->label.widget, 1, 1, 1, 2);
					grid->add(grid, &lbl_display2->label.widget, 2, 1, 1, 2);
					grid->add(grid, &lbl_display3->label.widget, 3, 1, 1, 2);
					grid->add(grid, &lbl_datefromfile->label.widget,1, 3,1,2);
					grid->add(grid, &lbl_dayofweek->label.widget, 2, 3, 1, 2);
					grid->add(grid, &lbl_weekofyear->label.widget, 3, 3, 1, 2);
				    
					window_resize(main_window, 500,500);
			
					window_exec(main_window);
					task_retval(0);
					async_manager();
					return 1;
					}
					else {
						printf("Compositor server not specified.\n");
						return 1;
					}					
		return 0;
}
