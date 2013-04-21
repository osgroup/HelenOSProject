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

/** @addtogroup calculator
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
			#define NAME "calculator"
			#define SIZE 100
			int stack[SIZE];
			int top=-1;
			int flags=0;

		 
		typedef struct x_label {
				label_t label;
				slot_t btn_1;
				slot_t btn_2;
				slot_t btn_3;
				slot_t btn_4;
				slot_t btn_5;
				slot_t btn_6;
				slot_t btn_7;
				slot_t btn_8;
				slot_t btn_9;
				slot_t btn_0;
				slot_t btn1;
				slot_t btn2;
				slot_t btn3;
				slot_t btn4;
				slot_t btn5;
				slot_t btn6;
			} x_label_t;
		
	static	void push(int data)
{
    if(top==SIZE-1)
    {
        printf("Stack is full\n");
        return;
    }
    else
    {
        top=top+1;
        stack[top]=data;
        //printf("Pushed element is %c\n",data);
    }
}

static int pop()
{
    int ch;
    if(top<0)
    {
        printf("stack is empty\n");
        return 0;
    }
    else
    {
        ch=stack[top];
        //printf("poped element is%c\n",ch);
        top=top-1;
        return (ch);
    }
}


static int check_pre(char a ,char b)
{
    //operators are arranged in the array based
    //on their priority. from low to high

    int op[]= {-1,-2,-3,-4,-5,-6};
    int i,c1=0,c2=0;
    for(i=0; i<6; i++)
    {
        if(a==op[i])
            c1=i+1;
        else if(b==op[i])
            c2=i+1;
    }
    if(c1>c2)
        return(1);
    else if(c1<c2)
        return(-1);
    else
        return(0);
}

static int evaluate(int op1, int op2,int ch)
{
    //printf("op1=%d op2=%d ch=%c\n",op1,op2,ch);
    int n;
    if (op1<op2)
    {
        n=op1;
        op1=op2;
        op2=n;
    }
    if(ch==-2)
        n=op1+op2;
    else if(ch==-1)
        n=op1-op2;
    else if(ch==-4)
        n=op1*op2;
    else if(ch==-3)
        n=op1/op2;
    else
    {
        printf("The operator is not identified\n");
        exit(0);
    }
    //printf("n=%d\n",n);
    return(n);
}

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
			
			static void onClick_btn_1(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "1";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "1";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0 && flags == 1)
				{
					flags=0;
					const char *confirmed = "1";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_2(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "2";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "2";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_3(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "3";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "3";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_4(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "4";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "4";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_5(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "5";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "5";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_6(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "6";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "6";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_7(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "7";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "7";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_8(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "8";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "8";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_9(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "9";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "9";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn_0(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "0";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "0";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn1(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "+";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "+";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn2(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "-";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "-";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn3(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "*";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "*";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			static void onClick_btn4(widget_t *widget, void *data)
			{
				x_label_t *lbl = (x_label_t *) widget;
				
				const char *newText = "/";
				char* currentText ;
				currentText = str_dup((&lbl->label)->caption);
			
				if(str_cmp(currentText,".") == 0)
				{
					const char *confirmed = "/";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
				}
				else if( currentText != NULL && str_cmp(currentText,".") != 0)
				{
					char *c = malloc (sizeof(newText) + sizeof(currentText) + 1);
					if ( c != NULL)
					{
						c=str_dup(currentText);
						//printf("\nbefore: %s", c);
						str_append(c,str_size(c)+str_size(currentText)+1,newText);
			            //printf("\nafter: %s", c);
						
						const char *confirmed1 = str_dup(c);
						//printf("\ntext writing to label %s\n", confirmed1);
						lbl->label.rewrite(&lbl->label.widget, (void *)confirmed1);
					}
				}
			}
			
			//code for = button
			static void onClick_btn5(widget_t *widget, void *data)
			{
				
				x_label_t *lbl = (x_label_t *) widget;
				
				char* infix;
				infix = str_dup((&lbl->label)->caption);
				
				if(str_cmp(infix,".") == 0)
				{
					printf("\nno input\n");
					const char *confirmed1 = ".";
					lbl->label.rewrite(&lbl->label.widget, (void *) confirmed1);
				}
				else if( infix != NULL && str_cmp(infix,".") != 0 && flags == 0)
				{
					/*str_cpy(in, str_size(currentText)+1, currentText);
				        int k=0;
					printf("data in IN array: \n");
					do{
						printf("%c",in[k]);
						k++;
					}while(in[k] != '\0');
					k=0;
					post();
					root = exptree();
					
					int res = eval(root);
					printf("\nresult BEFORE CONVERT is: %d\n", res);
					char *result=(char *)malloc(sizeof(char)*100);					
					//converting int res into char* result
					
					snprintf(result,25,"%d",res);
					printf("\nresult AFTER CONVERT is: %s\n", result);*/
					
					
					int postfix[50];
					int postfix_len=0;
					int flag=0;
					//char ch;
					int temp;
					int pre=0;
					int i;
					for( i=0; infix[i]!='\0'; i++)
					{
					char ch=infix[i];
					if(ch>='0' && ch<='9')
					{
					if(postfix_len>0 && flag==1)
					{
					postfix[postfix_len-1]=postfix[postfix_len-1]*10+(ch-48);
					}
					else
					{
					postfix[postfix_len]=ch-48;
					postfix_len++;
					flag=1;					// flag i m controlling digits...
					}
					}
					
					//for '(' paranthesis
					else if(ch=='(')
					{
					push(-5);
					flag=0;
					}
					
					//for ')' parenthesis
					else if(ch==')')
					{
					flag=0;
					temp=pop();
					while(temp!=-5)
					{
					
					postfix[postfix_len]=temp;
					postfix_len++;
					temp=pop();
					}
					}
					else
					{
					
					flag=0;
					if (top==-1 || stack[top]==-5)
					{	if(ch=='-')
					push(-1);
					if(ch=='+')
					push(-2);
					if(ch=='/')
					push(-3);
					if(ch=='*')
					push(-4);
					}
					
					else
					{
					temp=stack[top];
					
					//check the precedence
					if(ch=='-')
					pre=check_pre(-1,temp);
					if(ch=='+')
					pre=check_pre(-2,temp);
					if(ch=='/')
					pre=check_pre(-3,temp);
					if(ch=='*')
					pre=check_pre(-4,temp);
					if(pre<0 )
					{
                    do
                    {
					postfix[postfix_len]=pop();
					postfix_len++;
					temp=stack[top];
                    }
					while( top!=-1  &&  temp!=-5  &&  ( (check_pre(-1,temp)|| check_pre(-2,temp)||check_pre(-3,temp)||check_pre(-4,temp))<0) );
					if(ch=='-')
					push(-1);
					else	if(ch=='+')
					push(-2);
					else	if(ch=='/')
					push(-3);
					else	if(ch=='*')
					push(-4);
					}
					else
					{
					if(ch=='-')
					push(-1);
					if(ch=='+')
					push(-2);
					if(ch=='/')
					push(-3);
					if(ch=='*')
					push(-4);
					}
					}
					}
					}
					
					while(top!=-1)
					{
					postfix[postfix_len]=pop();
					postfix_len++;
					}
					
					/*printf("Postfix string=");
					int j;
					for( j=0; j<postfix_len; j++)
					{
					if(postfix[j]>=0)
					// printf("%d ",postfix[j]);
					else
					{
					if(postfix[j]==-1)
					printf("- ");
					else if(postfix[j]==-2)
					printf("+ ");
					else if(postfix[j]==-3)
					printf("/ ");
					else if(postfix[j]==-4)
					printf("* ");
					}
					}
					printf("\n");*/
					
					
					int op1,op2,k;
					
					for( k=0; k<postfix_len; k++)
					{
					if(postfix[k]>=0)
					{
					push(postfix[k]);
					}
					else
					{
					op1=pop();
					op2=pop();
					push(evaluate(op1,op2,postfix[k]));
					}
					}
					char *result=(char *)malloc(sizeof(char)*100);					
					//converting int res into char* result
					
					snprintf(result,25,"%d",pop());				
    					const char *confirmed = str_dup(result);
					lbl->label.rewrite(&lbl->label.widget, (void *)confirmed);				
					flags=1;
				}
			}
			
			static void onClick_btn6(widget_t *widget, void *data)
			{
				flags=0;
				x_label_t *lbl = (x_label_t *) widget;
				const char *confirmed = ".";
				lbl->label.rewrite(&lbl->label.widget, (void *) confirmed);
			}
			
			static bool init_x_label(x_label_t *lbl, widget_t *parent,
				const char *caption, uint16_t points, pixel_t background, pixel_t foreground)
			{
				lbl->btn_1 = onClick_btn_1;
				lbl->btn_2 = onClick_btn_2;
				lbl->btn_3 = onClick_btn_3;
				lbl->btn_4 = onClick_btn_4;
				lbl->btn_5 = onClick_btn_5;
				lbl->btn_6 = onClick_btn_6;
				lbl->btn_7 = onClick_btn_7;
				lbl->btn_8 = onClick_btn_8;
				lbl->btn_9 = onClick_btn_9;
				lbl->btn_0 = onClick_btn_0;
				lbl->btn1 = onClick_btn1;
				lbl->btn2 = onClick_btn2;
				lbl->btn3 = onClick_btn3;
				lbl->btn4 = onClick_btn4;
				lbl->btn5 = onClick_btn5;
			        lbl->btn6 = onClick_btn6;
			    
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
			
			int main(int argc, char *argv[])
			{
				if (argc >= 2) {
					window_t *main_window = window_open(argv[1], true, true, "X-Calc", 255, 255);
					if (!main_window) {
						printf("Cannot open main window.\n");
						return 1;
					}
			
					pixel_t grd_bg = PIXEL(255, 240, 240, 240);

					pixel_t btn_bg = PIXEL(255, 0, 0, 0);
					pixel_t btn_fg = PIXEL(200, 200, 200, 200);
					
					pixel_t lbl_bg = PIXEL(255, 240, 240, 240);
					pixel_t lbl_fg = PIXEL(255, 0, 0, 0);
			
					//label_t *lbl_caption = create_label(NULL,"calculator", 16, lbl_bg, lbl_fg);
					grid_t *grid = create_grid(window_root(main_window), 5, 4, grd_bg);
					x_label_t *lbl_display = create_x_label(NULL, ".", 16, lbl_bg, lbl_fg);
					
					button_t *btn_1 = create_button(NULL, "1", 16, btn_bg, btn_fg);
					button_t *btn_2 = create_button(NULL, "2", 16, btn_bg, btn_fg);
					button_t *btn_3 = create_button(NULL, "3", 16, btn_bg, btn_fg);
					button_t *btn_4 = create_button(NULL, "4", 16, btn_bg, btn_fg);
					button_t *btn_5 = create_button(NULL, "5", 16, btn_bg, btn_fg);
					button_t *btn_6 = create_button(NULL, "6", 16, btn_bg, btn_fg);
					button_t *btn_7 = create_button(NULL, "7", 16, btn_bg, btn_fg);
					button_t *btn_8 = create_button(NULL, "8", 16, btn_bg, btn_fg);
					button_t *btn_9 = create_button(NULL, "9", 16, btn_bg, btn_fg);
					button_t *btn_0 = create_button(NULL, "0", 16, btn_bg, btn_fg);
					button_t *btn1 = create_button(NULL, "+", 16, btn_bg, btn_fg);
					button_t *btn2 = create_button(NULL, "-", 16, btn_bg, btn_fg);
					button_t *btn3 = create_button(NULL, "*", 16, btn_bg, btn_fg);
					button_t *btn4 = create_button(NULL, "/", 16, btn_bg, btn_fg);
					button_t *btn5 = create_button(NULL, "=", 16, btn_bg, btn_fg);
					button_t *btn6 = create_button(NULL, "C", 16, btn_bg, btn_fg);
			
					if (!lbl_display || !btn_1 || !btn_2 || !btn_3 || !btn_4 || 
						!btn_5 || !btn_6 || !btn_7 || !btn_8 || !btn_9 || !btn_0 || !btn1 || 
								!btn2 || !btn3 || !btn4 || !btn5 || !btn6 || !grid) 
					{
						window_close(main_window);
						printf("Cannot create widgets.\n");
						return 1;
					}
			
					/* button connection codes*/
					sig_connect(
						&btn_1->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_1);
					sig_connect(
						&btn_2->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_2);
					sig_connect(
						&btn_3->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_3);
					sig_connect(
						&btn_4->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_4);
					sig_connect(
						&btn_5->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_5);
					sig_connect(
						&btn_6->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_6);
					sig_connect(
						&btn_7->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_7);
					sig_connect(
						&btn_8->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_8);
					sig_connect(
						&btn_9->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_9);
					sig_connect(
						&btn_0->clicked,
						&lbl_display->label.widget,
						lbl_display->btn_0);
					sig_connect(
						&btn1->clicked,
						&lbl_display->label.widget,
						lbl_display->btn1);
					sig_connect(
						&btn2->clicked,
						&lbl_display->label.widget,
						lbl_display->btn2);
					sig_connect(
						&btn3->clicked,
						&lbl_display->label.widget,
						lbl_display->btn3);
					sig_connect(
						&btn4->clicked,
						&lbl_display->label.widget,
						lbl_display->btn4);
					sig_connect(
						&btn5->clicked,
						&lbl_display->label.widget,
						lbl_display->btn5);
					sig_connect(
						&btn6->clicked,
						&lbl_display->label.widget,
						lbl_display->btn6);
	
						//grid->add(grid, &lbl_caption->widget, 0, 0, 1, 4);
						grid->add(grid, &lbl_display->label.widget, 0, 0, 1, 4);
						grid->add(grid, &btn_1->widget, 1, 0, 1, 1);
						grid->add(grid, &btn_2->widget, 1, 1, 1, 1);
						grid->add(grid, &btn_3->widget, 1, 2, 1, 1);
						grid->add(grid, &btn_4->widget, 2, 0, 1, 1);
						grid->add(grid, &btn_5->widget, 2, 1, 1, 1);
						grid->add(grid, &btn_6->widget, 2, 2, 1, 1);
						grid->add(grid, &btn_7->widget, 3, 0, 1, 1);
						grid->add(grid, &btn_8->widget, 3, 1, 1, 1);
						grid->add(grid, &btn_9->widget, 3, 2, 1, 1);
						grid->add(grid, &btn_0->widget, 4, 0, 1, 1);
						grid->add(grid, &btn1->widget, 1, 3, 1, 1);
						grid->add(grid, &btn2->widget, 2, 3, 1, 1);
						grid->add(grid, &btn3->widget, 3, 3, 1, 1);
						grid->add(grid, &btn4->widget, 4, 3, 1, 1);
						grid->add(grid, &btn5->widget, 4, 2, 1, 1); 
						grid->add(grid, &btn6->widget, 4, 1, 1, 1); 
						window_resize(main_window, 400, 400);
						
						window_exec(main_window);
						task_retval(0);
						async_manager();
						return 1;
					}
					else {
						printf("Compositor server not specified.\n");
						return 1;
					}		
			}
	
