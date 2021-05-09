// parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "calc_tab.h"
#include "calc.cc"
#include "calc_tab.cc"

int main(int argc, char* argv[])
{
//	char s[100];
//	fgets(s,20,stdin);
//	yyin="1 1 +";//fopen( "test.txt", "r" ); iobuf
	char *c="1 1 + \n";
	yy_scan_string(c);
//    calclex();
	calcparse();
//    printf(yyout);
	return 0;
}

