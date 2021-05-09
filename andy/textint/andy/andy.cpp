// andy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "andy_tab.h"
#include "andy.cc"
#include "andy_tab.cc"

int main(int argc, char* argv[])
{
	yy_scan_string("1 1 +\n");
	andyparse();
	return 0;
}

