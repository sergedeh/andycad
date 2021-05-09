cd c:\yacc\bin
bison -d -l -p andy c:\yacc\bin\andy\andy.y 
move andy.tab.c c:\yacc\bin\andy\andy_tab.cc

move andy.tab.h c:\yacc\bin\andy\andy_tab.h
flex -L -Pandy -oc:\yacc\bin\andy\andy.cc c:\yacc\bin\andy\andy.l

cd c:\yacc\bin\andy