%option noyywrap
%{
#include <io.h>
#include <string.h>
#define isatty _isatty
%}
con "con"
op "and"|"or"
bit  1|2|0
%%
{con}  {
		return con;
		}
{op}	{
		if(!strcmp(yytext,"and"))
		  digilval=1;
		else
		if(!strcmp(yytext,"or"))
		  digilval=2;
		return op;
		}
{bit}	{
		  digilval=atoi(&yytext[0]);
		  return bit;
		}
[\n]    {
		  return *yytext;
		}		
%%