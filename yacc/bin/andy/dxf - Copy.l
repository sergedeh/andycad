%option noyywrap
%option stack
%s entity
%s line_entity
%s next_entity
%s line_entry
%s entity_code
%s entity_value
%s single
%s _header
%s block_code
%s block_value

%s block
%{
#include <io.h>
#include <queue>
#include <deque>
#define isatty _isatty

using namespace std;
typedef map<int,float> fmap;
typedef vector<int> ivec;

fmap dxfvf;
ivec dxfvi;
int group_code=-1;

%}
error2 "error2"
_ret \n[ \t]*
_space [ \t]*
HEADER_START {_space}0{_ret}SECTION{_ret}2{_ret}HEADER{_ret}
SECTION_END {_space}0{_ret}ENDSEC{_ret}
VAR_NAME $[[:alnum:]]+
VALUE num
HEADER_GROUP_CODE 70|1|50|62|40|6|370|390|380|8|2|280|7|349|3|10|20|30|290|5|345|346
HEADER_VAR 9{_ret}{_string}{_ret}({_space}{HEADER_GROUP_CODE}{_ret}({_string})?{_ret})+

CLASS_START 0{_ret}SECTION{_ret}2{_ret}CLASSES{_ret}
PROXY_FLAG "0"|"1"|"2"|"4"|"8"|"16"|"32"|"64"|"128"|"256"|"512"|"895"|"1023"|"1024"|"32768"
WAS_PROXY_FLAG 0|1
IS_ENTITY_FLAG 0|1
CLASS_GROUP_CODE 1|2|3|90|280|281
CLASS_ENTRY 0{_ret}CLASS{_ret}({_space}{CLASS_GROUP_CODE}{_ret}({_string})?{_ret}){6}

TABLE_START {_space}0{_ret}SECTION{_ret}2{_ret}TABLES{_ret}
_100_TABLE {_space}100{_ret}AcDbSymbolTable{_ret}
TABLE_GROUP_CODE 2|5|70|102|360|330
TABLE_ENTRY {_space}0{_ret}TABLE{_ret}({_space}{TABLE_GROUP_CODE}{_ret}{_string}?{_ret}|{_100_TABLE})+
TABLE_END {_space}0{_ret}ENDTAB{_ret}

_100_TABLEENTRY {_space}100{_ret}AcDbSymbolTableRecord{_ret} 
TABLECMN_GROUP_CODE 105|5|330
TABLE_CMN_GROUP {_space}0{_ret}(VPORT|VIEW|BLOCK_RECORD|APPID|LAYER|DIMSTYLE|LTYPE|STYLE|UCS){_ret}({_space}{TABLECMN_GROUP_CODE}{_ret}{_string}?{_ret}|{_100_TABLEENTRY})+

_100_APPID_TABLEENTRY 100{_ret}AcDbRegAppTableRecord
APPID_GROUP_CODE 2|70
APPID_ENTRY {_space}100{_ret}AcDbRegAppTableRecord{_ret}({_space}{APPID_GROUP_CODE}{_ret}{_string}?{_ret})+

BLOCK_GROUP_CODE 2|70|340|280|281
BLOCK_RECORD_ENTRY {_space}100{_ret}AcDbBlockTableRecord{_ret}({_space}{BLOCK_GROUP_CODE}{_ret}{_string}?{_ret})+

DIMSTYLE_GROUP_CODE 2|70|3|4|5|6|7|40|41|42|43|44|45|46|47|48|140|141|142|143|144|145|146|147|148|71|72|73|74|75|76|77|78|79|170|171|172|173|174|175|176|177|178|179|270|271|272|273|274|275|276|277|278|279|280|281|282|283|284|285|286|287|288|289|340|341|342|343|344|371|372
DIMSTYLE_ENTRY {_space}100{_ret}AcDbDimStyleTableRecord{_ret}({_space}{DIMSTYLE_GROUP_CODE}{_ret}{_string}?{_ret})+

LAYER_GROUP_CODE 2|70|62|6|290|370|390|347
LAYER_ENTRY {_space}100{_ret}AcDbLayerTableRecord{_ret}({_space}{LAYER_GROUP_CODE}{_ret}{_string}?{_ret})+ 

LTYPE_GROUP_CODE 2|70|3|72|73|40|49|75|340|46|50|44|45|9
LTYPE_ENTRY {_space}100{_ret}AcDbLinetypeTableRecord{_ret}({_space}{LTYPE_GROUP_CODE}{_ret}{_string}?{_ret}){5,14} 

STYLE_GROUP_CODE 2|70|40|41|50|71|42|3|4|1071|1001|1000
STYLE_ENTRY {_space}100{_ret}AcDbTextStyleTableRecord{_ret}({_space}{STYLE_GROUP_CODE}{_ret}{_string}?{_ret})+ 

UCS_GROUP_CODE 2|70|10|20|30|11|21|31|12|22|32|79|146|346|71|13|23|33
UCS_ENTRY {_space}100{_ret}AcDbUCSTableRecord{_ret}({_space}{UCS_GROUP_CODE}{_ret}{_string}?{_ret})+ 

VIEW_GROUP_CODE 2|70|10|20|41|11|21|31|12|22|32|42|43|44]|50|71|281|72|73|332|334|348|361|110|120|130|111|121|131|112|122|132|79|146|345|346
VIEW_ENTRY {_space}100{_ret}AcDbViewTableRecord{_ret}({_space}{VIEW_GROUP_CODE}{_ret}{_string}?{_ret})+ 

VPORT_GROUP_CODE 2|10|11|12|13|14|15|16|17|20|21|22|23|24|25|26|27|40|41|42|43|44|45|70|71|72|73|74|75|76|77|78|79|36|37|50|51|331|332|333|441|1|281|282|110|111|112|121|122|131|132|345|346|146|170|61|348|292|141|142|63|421|431
VPORT_ENTRY {_space}100{_ret}AcDbViewportTableRecord{_ret}({_space}{VPORT_GROUP_CODE}{_ret}{_string}?{_ret})+

TABLE_ENTRY_DATA1 {APPID_ENTRY}|{BLOCK_RECORD_ENTRY}|{DIMSTYLE_ENTRY}|{LAYER_ENTRY}|{LTYPE_ENTRY}|{STYLE_ENTRY}|{UCS_ENTRY}|{VIEW_ENTRY}|{VPORT_ENTRY}

BLOCK_START {_space}0{_ret}SECTION{_ret}2{_ret}BLOCKS{_ret}
BLOCK2_GROUP_CODE 2|5|70|102|330|100|8|10|20|30|3|1|4|67
BLOCK_ENTRY {_space}0{_ret}BLOCK{_ret}({_space}{BLOCK2_GROUP_CODE}{_ret}{_string}?{_ret})+
BLOCKEND_GROUP_CODE 5|102|360|330|100|8|67
/*BLOCKEND_ENTRY {_space}0{_ret}ENDBLK{_ret}({_space}{BLOCKEND_GROUP_CODE}{_ret}{_string}?{_ret})+*/

ENTITY_START {_space}0{_ret}SECTION{_ret}2{_ret}ENTITIES{_ret}
ENTITYCMN_GROUP_CODE 102|5|330|360|67|410|8|6|347|62|370|48|60|92|310|420|430|440|390|284
_100_ENTITYENTRY {_space}100{_ret}AcDbEntity{_ret} 
ENTITY_CMN_TYPE ^{_space}(ARC|ATTDEF|ATTRIB|CIRCLE|DIMENSION|ELLIPSE|HATCH|IMAGE|INSERT|LEADER|LINE|SPLINE|TEXT|VIEWPORT)
/*ENTITY_CMN_GROUP {_space}0{_ret}{ENTITY_CMN_TYPE}{_ret}({_space}{ENTITYCMN_GROUP_CODE}{_ret}{_string}?{_ret}|{_100_ENTITYENTRY})+*/

ARC_GROUP_CODE 39|10|20|30|40|70|340|280|281|50|51|210|220|230
ARC_ENTRY {_space}100{_ret}AcDbCircle{_ret}100{_ret}AcDbArc{_ret}({_space}{ARC_GROUP_CODE}{_ret}{_string}?{_ret})+

CIRCLE_GROUP_CODE 39|10|20|30|40|210|220|230
CIRCLE_ENTRY {_space}100{_ret}AcDbCircle{_ret}({_space}{CIRCLE_GROUP_CODE}{_ret}{_string}?{_ret})+

LINE_GROUP_CODE 39|10|20|30|11|21|31|210|220|230
LINE_ENTRY_START {_space}100{_ret}AcDbLine{_ret}
/*LINE_ENTRY {_space}100{_ret}AcDbLine{_ret}({_space}{LINE_GROUP_CODE}{_ret}{_string}?{_ret})+*/

SPLINE_GROUP_CODE 70|71|72|73|74|210|220|230|42|43|44|12|22|32|13|23|33|40|41|10|20|30|11|21|31
SPLINE_ENTRY {_space}100{_ret}AcDbSpline{_ret}({_space}{SPLINE_GROUP_CODE}{_ret}{_string}?{_ret})+

TEXT_GROUP_CODE 39|10|20|30|40|1|41|51|7|71|72|11|21|31|210|220|230|100|73
TEXT_ENTRY {_space}100{_ret}AcDbText{_ret}({_space}{TEXT_GROUP_CODE}{_ret}{_string}?{_ret})+

DIMENSION_GROUP_CODE 280|2|10|20|30|11|21|31|70|71|72|42|1|41|53|51|210|220|230|3
DIMENSION_ENTRY {_space}100{_ret}AcDbDimension{_ret}({_space}{DIMENSION_GROUP_CODE}{_ret}{_string}?{_ret})+

ALDIMENSION_GROUP_CODE 12|22|32|13|23|33|14|24|34
ALDIMENSION_ENTRY {_space}100{_ret}AcDbAlignedDimension{_ret}({_space}{ALDIMENSION_GROUP_CODE}{_ret}{_string}?{_ret})+

LRDIMENSION_GROUP_CODE 12|22|32|13|23|33|14|24|34|50|52
LRDIMENSION_ENTRY {_space}100{_ret}AcDbAlignedDimension{_ret}AcDbRotatedDimension{_ret}({_space}{LRDIMENSION_GROUP_CODE}{_ret}{_string}?{_ret})+

RDIMENSION_GROUP_CODE 15|25|35|40
RDIMENSION_ENTRY {_space}100{_ret}(AcDbRadialDimension|AcDbDiametricDimension){_ret}({_space}{RDIMENSION_GROUP_CODE}{_ret}{_string}?{_ret})+

ANDIMENSION_GROUP_CODE 13|23|33|14|24|34|15|25|35|16|26|36
ANDIMENSION_ENTRY {_space}100{_ret}AcDb3PointAngularDimension{_ret}({_space}{ANDIMENSION_GROUP_CODE}{_ret}{_string}?{_ret})+

ODIMENSION_GROUP_CODE 13|23|33|14|24|34
ODIMENSION_ENTRY {_space}100{_ret}AcDbOrdinateDimension{_ret}({_space}{ODIMENSION_GROUP_CODE}{_ret}{_string}?{_ret})+

ENTITY_ENTRY_DATA1 {ARC_ENTRY}|{CIRCLE_ENTRY}|{LINE_ENTRY}|{SPLINE_ENTRY}|{TEXT_ENTRY}|{DIMENSION}
_string [^\n]+

%%
<block,entity,entity_code,next_entity>{ENTITY_CMN_TYPE} {
		char* _s=yytext;
		if(strcmp(_s,"LINE")==0)
		{
         yy_push_state(line_entity);
         yy_push_state(entity_code);
		}
		return ENTITY_CMN_TYPE;
	}
<entity_code>{LINE_ENTRY_START} {
		        yy_pop_state();				
		        yy_push_state(line_entry);				
		        return LINE_ENTRY_START;
				}
<line_entry>{LINE_GROUP_CODE} {
				group_code=atoi(yytext);
		        yy_push_state(entity_value);	
				dxfvi.push_back(LINE_GROUP_CODE);			
					return LINE_GROUP_CODE;
				}
{HEADER_START}  {
		yy_push_state(_header);
		return HEADER_START;
		}
<_header>{HEADER_VAR}  {
		return HEADER_VAR;
		}
{CLASS_START}  {
		return CLASS_START;
		}
{CLASS_ENTRY}  {
		return CLASS_ENTRY;
		}
{SECTION_END}  {
		return SECTION_END;
		}
{TABLE_START}  {
		return TABLE_START;
		}
{TABLE_ENTRY}  {
		return TABLE_ENTRY;
		}
{TABLE_CMN_GROUP}  {
		return TABLE_CMN_GROUP;
		}
{TABLE_END} {
		 return TABLE_END;
		}
{TABLE_ENTRY_DATA1} {
		 return TABLE_ENTRY_DATA1;
		}
{BLOCK_START} {
		 return BLOCK_START;
		}
{BLOCK_ENTRY} {
		yy_push_state(block);
		 return BLOCK_ENTRY;
		}
<block,block_code>{BLOCKEND_GROUP_CODE} {
        yy_push_state(block_value);	
		return BLOCKEND_GROUP_CODE;
		}
{ARC_ENTRY} {
		 return ARC_ENTRY;
		}
{CIRCLE_ENTRY} {
		 return CIRCLE_ENTRY;
		}
{SPLINE_ENTRY} {
		 return SPLINE_ENTRY;
		}
{TEXT_ENTRY} {
		 return TEXT_ENTRY;
		}
{ODIMENSION_ENTRY} {
		 return ODIMENSION_ENTRY;
		}
{ANDIMENSION_ENTRY} {
		 return ANDIMENSION_ENTRY;
		}
{RDIMENSION_ENTRY} {
		 return RDIMENSION_ENTRY;
		}
{LRDIMENSION_ENTRY} {
		 return LRDIMENSION_ENTRY;
		}
{ALDIMENSION_ENTRY} {
		 return ALDIMENSION_ENTRY;
		}
{DIMENSION_ENTRY} {
		 return DIMENSION_ENTRY;
		}

{ENTITY_START} {
		 yy_push_state(entity);
		 return ENTITY_START;
		}
<block,entity_code,entity_value>{_100_ENTITYENTRY} {
		 return _100_ENTITYENTRY;
		}
<entity_code,entity_value>{ENTITYCMN_GROUP_CODE} {
		 yy_push_state(entity_value);
		 return ENTITYCMN_GROUP_CODE;
		}
"ENDBLK" {
			yy_push_state(block);
			return endblock;
		}
<entity_value,block_value>{_string}  {
		 yy_pop_state();
		 char* __string=yytext;
		 if(dxfvi.size()>0)
		 {
		 int i=dxfvi.back();
		 if(i==LINE_GROUP_CODE)
		 {
			float v=atof(__string);
			dxfvf.insert(make_pair(group_code,v));
			dxfvi.pop_back();
			 yy_pop_state();
			 yy_push_state(line_entry);

		 }
		 }
		 return _string;
		}
<single,block,line_entry>[^ \t\n] {	char cd=yytext[0];
				   int i=yy_top_state();
				//	yy_pop_state();
				   if(i==line_entity)
				   { 
				      yy_push_state(next_entity);
					}
					if(i==block)
					{
						yy_push_state(block);
					}
					return cd; }

%%