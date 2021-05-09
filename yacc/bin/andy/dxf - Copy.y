%{
#include <malloc.h>
#define alloc _alloc
#include <stdio.h>
#include <vector>
using namespace std;


vector<CVector> dxfpvec;
CString _out,dxfcom;
CCadDoc* dxfpDoc;
CCadView *dxfpView;
CVector dxfcv;
int _token=-1;
CStringArray sar;


yyerror (char* s)  /* Called by yyparse on error */
{
 // printf ("%s\n", s);
  CString f(s);
  sar.Add(_out+f);
}
%}
/* Digital electronic simulator. */
%token HEADER_START HEADER_VAR SECTION_END EOL VAR_NAME VALUE GROUP_CODE TABLE_END
%token TABLE_CMN_GROUP TABLE_START TABLE_ENTRY TABLE_ENTRY_DATA1 CLASS_ENTRY CLASS_START error2
%token BLOCK_START BLOCK_ENTRY BLOCKEND_GROUP_CODE LINE_ENTRY_START
%token ENTITY_START LINE_GROUP_CODE _100_ENTITYENTRY ENTITY_CMN_TYPE ENTITYCMN_GROUP_CODE
%token DIMENSION_ENTRY ALDIMENSION_ENTRY LRDIMENSION_ENTRY RDIMENSION_ENTRY ANDIMENSION_ENTRY ODIMENSION_ENTRY
%token ARC_ENTRY CIRCLE_ENTRY LINE_ENTRY SPLINE_ENTRY TEXT_ENTRY
%token _space _ret _string
%token endblock "ENDBLK"
%error-verbose 


%% /* Grammar rules and actions follow */

input: /*empty*/
		|input TABLES 
		|input BLOCKS
		|input ENTITIES ;

HEADER: HEADER_START {_out="Catching an Header Start \n";
							 yyerror(yytext);} HEADER_VARS SECTION_END {_out="Catching a Section End \n";
																				yyerror(yytext);};
HEADER_VARS: /*empty*/
			 |HEADER_VAR {_out="Catching an Header variable \n";
							yyerror(yytext);} HEADER_VARS;
CLASSES: CLASS_START {_out="Catching a Class Start \n";
							 yyerror(yytext);} CLASS_ENTRIES SECTION_END {_out="Catching a Section End \n";
																				yyerror(yytext);};
CLASS_ENTRIES: /*empty*/
				|CLASS_ENTRY {_out="Catching a Class Entry \n";
							yyerror(yytext);} CLASS_ENTRIES;
TABLES:  TABLE_START {_out="Catching a Table Start \n";
							 yyerror(yytext);} TABLE_ENTRIES SECTION_END {_out="Catching a Table Section End \n";
							 yyerror(yytext);};
TABLE_ENTRY1:  TABLE_ENTRY {_out="Catching a Table Entry \n";
							 yyerror(yytext);} TABLE_ENTRY_DATA TABLE_END {_out="Catching a Table End \n";
							 yyerror(yytext);};
TABLE_ENTRIES: TABLE_ENTRY1
				|TABLE_ENTRIES TABLE_ENTRY1 ;

TABLE_ENTRY_DATA:	/*empty*/
					|TABLE_CMN_GROUP {_out="Catching a Table Common Entry Data \n";
							 yyerror(yytext);} TABLE_ENTRY_DATA1 {_out="Catching a Table Entry Data \n";
							 yyerror(yytext);}
					|TABLE_ENTRY_DATA TABLE_CMN_GROUP {_out="Catching a Table Common Entry Data \n";
							 yyerror(yytext);} TABLE_ENTRY_DATA1 {_out="Catching a Table Entry Data \n";
							 yyerror(yytext);} ;
BLOCKS: BLOCK_START {_out="Catching a Block Start \n";
							 yyerror(yytext);} BLOCK_ENTRIES SECTION_END {_out="Catching a Block Section End \n";
							 yyerror(yytext);};
BLOCK_ENTRIES: BLOCK_ENTRY1
				|BLOCK_ENTRIES BLOCK_ENTRY1; 
BLOCK_ENTRY1:  BLOCK_ENTRY {_out="Catching a Block Entry \n";
							 yyerror(yytext);} BLOCK_ENTRY2 {_out="Catching a Block End Entry\n";
							 yyerror(yytext);}
BLOCK_ENTRY2: '0' "ENDBLK" BLOCKEND_ENTRY_CODE
			  |ENTITY_ENTRIES '0' "ENDBLK" BLOCKEND_ENTRY_CODE

BLOCKEND_ENTRY_CODE: BLOCKEND_GROUP_CODE
					| BLOCKEND_GROUP_CODE _string
					|_100_ENTITYENTRY
					|BLOCKEND_ENTRY_CODE _100_ENTITYENTRY
					|BLOCKEND_ENTRY_CODE BLOCKEND_GROUP_CODE
					|BLOCKEND_ENTRY_CODE BLOCKEND_GROUP_CODE _string ; 

ENTITY_ENTRIES:  ENTITY_ENTRY1
				|ENTITY_ENTRIES ENTITY_ENTRY1; 
ENTITY_ENTRY1:  '0' {_out="Catching the 0 of CMN Group"}  ENTITY_CMN_TYPE {_out="Catching the CMN TYPE"} ENTITYCMN_GROUP_CODE1 
				ENTITY_ENTRY_DATA1 {_out="Catching an Entity Entry Data \n";
							 yyerror(yytext);};
ENTITYCMN_GROUP_CODE1: ENTITYCMN_GROUP_CODE {_out="Catching an Entity Common Group Code \n";
							 yyerror(yytext);}  _string {_out="Catching an Common Group Code Value \n";
							 yyerror(yytext);} 
					  | ENTITYCMN_GROUP_CODE {_out="Catching an Entity Common Group Code \n";
							 yyerror(yytext);} 
					  |_100_ENTITYENTRY {_out="Catching an Entity 100 Common Group Code \n";
							 yyerror(yytext);}
					  |ENTITYCMN_GROUP_CODE1 ENTITYCMN_GROUP_CODE {_out="Catching a next Entity Common Group Code \n";
							 yyerror(yytext);} _string {_out="Catching a next Entity Common Group Code Value \n";
							 yyerror(yytext);} 
					  |ENTITYCMN_GROUP_CODE1  ENTITYCMN_GROUP_CODE {_out="Catching a next Entity Common Group Code \n";
							 yyerror(yytext);} 
					  |ENTITYCMN_GROUP_CODE1 _100_ENTITYENTRY {_out="Catching an Entity 100 Common Group Code \n";
							 yyerror(yytext);};

DIMENSION : DIMENSION_ENTRY ALDIMENSION_ENTRY|
			DIMENSION_ENTRY LRDIMENSION_ENTRY|
			DIMENSION_ENTRY RDIMENSION_ENTRY|
			DIMENSION_ENTRY ANDIMENSION_ENTRY|
			DIMENSION_ENTRY ODIMENSION_ENTRY;
ENTITY_ENTRY_DATA1: ARC_ENTRY|CIRCLE_ENTRY
					|LINE_ENTRY_START LINE_ENTRIES { 
					//								if(_token==ENTITY_START)
													{
														CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
														CVector ve(dxfvf[11],dxfvf[21],dxfvf[31]);
														dxfpvec.clear();
													//	dxfpvec.push_back(vo);
													//	dxfpvec.push_back(ve);
													//	dxfpDoc->m_objects->AddLine(dxfpvec);
													//	dxfpView->Invalidate(TRUE);
													}
								}
					|SPLINE_ENTRY|TEXT_ENTRY|DIMENSION;
LINE_ENTRIES: LINE_GROUP_CODE _string
			|LINE_ENTRIES LINE_GROUP_CODE _string {
													}
ENTITIES:  ENTITY_START {_out="Catching an Entity Start \n";
							 yyerror(yytext);
							 _token=ENTITY_START;
						} ENTITY_ENTRIES SECTION_END {_out="Catching a Block Section End \n";
														yyerror(yytext);
														_token=-1;
													 };

%%       