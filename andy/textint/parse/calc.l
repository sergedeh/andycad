%option noyywrap
%{
#include <io.h>
#define isatty _isatty
%}
DIGIT [0-9]
NUM {DIGIT}+|{DIGIT}+"."{DIGIT}*
op "+"|"-"|"*"|"/"|"\n"
%%
{NUM}  {
		calclval=atof(yytext); 
		return NUM;
		}
{op}	   {
		return yytext[0];
		}

%%