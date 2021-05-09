%{
#include <malloc.h>
#define alloc _alloc
#include <stdio.h>
int andf(int a, int b)
{
	return a*b;
}

int orf(int a, int b)
{
	return a+b;
}

yyerror (char* s)  /* Called by yyparse on error */
{
  printf ("%s\n", s);
}
%}
/* Digital electronic simulator. */
%token bit con op
%left con
%left op

%% /* Grammar rules and actions follow */

input:    /* empty */
        | input line

line:     '\n'
        | expr '\n' { printf ("\t%d\n", $1); }
expr:
	bit				{$$=$1;}
	|expr op expr
					{
						if(($1==2)||($3==2))
							$$=2;
						else
						{
						if($2==1)
							$$=andf($1,$3);
						else
						if($2==2)
							$$=orf($1,$3);
						}
					}
    |expr con expr
					{			
						if(($1==2)&&($3!=2))
							$$=$3;
						if($1!=2)
							$$=$1;
					}

%%       