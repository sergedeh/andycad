cd c:\yacc\bin
bison -d -l -p dxf c:\yacc\bin\andy\dxf.y --report=state -t
move dxf.tab.c c:\yacc\bin\andy\dxf_tab.c
move dxf.tab.h c:\yacc\bin\andy\dxf_tab.h
flex -L -Pdxf -oc:\yacc\bin\andy\dxf.c c:\yacc\bin\andy\dxf.l

cd c:\yacc\bin\andy