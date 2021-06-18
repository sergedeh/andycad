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
%s _table
%s block_code
%s block_value

%s block
%{
#include <io.h>
#include <sstream>
#include <string>
#include <queue>
#include <deque>
#define isatty _isatty

using namespace std;
typedef map<int,float> fmap;
typedef map<int,string> smap;
typedef map<int,vector<float> > vfmap;
typedef vector<int> ivec;

fmap dxfvf;
smap dxfvs;
vfmap vdxfvf;
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
BLOCKEND_ENTRY {_space}0{_ret}ENDBLK{_ret}({_space}{BLOCKEND_GROUP_CODE}{_ret}{_string}?{_ret})+

ENTITY_START {_space}0{_ret}SECTION{_ret}2{_ret}ENTITIES{_ret}
ENTITYCMN_GROUP_CODE 102|5|330|360|67|410|8|6|347|62|370|48|60|92|310|420|430|440|390|284
_100_ENTITYENTRY {_space}100{_ret}AcDbEntity{_ret} 
ENTITY_CMN_TYPE ARC|ATTDEF|ATTRIB|CIRCLE|DIMENSION|ELLIPSE|HATCH|IMAGE|INSERT|LEADER|LINE|SPLINE|TEXT|MTEXT|VIEWPORT|LWPOLYLINE
ENTITY_CMN_GROUP {_space}0{_ret}{ENTITY_CMN_TYPE}{_ret}({_space}{ENTITYCMN_GROUP_CODE}{_ret}{_string}?{_ret}|{_100_ENTITYENTRY})+

ARC_GROUP_CODE 39|10|20|30|40|70|340|280|281|50|51|210|220|230
ARC_ENTRY {_space}100{_ret}AcDbCircle{_ret}({_space}{CIRCLE_GROUP_CODE}{_ret}{_string}?{_ret})*{_space}100{_ret}AcDbArc{_ret}({_space}{ARC_GROUP_CODE}{_ret}{_string}?{_ret})+

CIRCLE_GROUP_CODE 39|10|20|30|40|210|220|230
CIRCLE_ENTRY {_space}100{_ret}AcDbCircle{_ret}({_space}{CIRCLE_GROUP_CODE}{_ret}{_string}?{_ret})+

LINE_GROUP_CODE 39|10|20|30|11|21|31|210|220|230
LINE_ENTRY_START {_space}100{_ret}AcDbLine{_ret}
LINE_ENTRY {_space}100{_ret}AcDbLine{_ret}({_space}{LINE_GROUP_CODE}{_ret}{_string}?{_ret})+

LWPOLYLINE_GROUP_CODE 90|70|43|38|39|10|20|91|40|41|42|210|220|230
LWPOLYLINE_ENTRY {_space}100{_ret}AcDbPolyline{_ret}({_space}{LWPOLYLINE_GROUP_CODE}{_ret}{_string}?{_ret})+

SPLINE_GROUP_CODE 70|71|72|73|74|210|220|230|42|43|44|12|22|32|13|23|33|40|41|10|20|30|11|21|31
SPLINE_ENTRY {_space}100{_ret}AcDbSpline{_ret}({_space}{SPLINE_GROUP_CODE}{_ret}{_string}?{_ret})+

TEXT_GROUP_CODE 39|10|20|30|40|1|41|51|7|71|72|11|21|31|210|220|230|100|73
TEXT_ENTRY {_space}100{_ret}AcDbText{_ret}({_space}{TEXT_GROUP_CODE}{_ret}{_string}?{_ret})+

MTEXT_GROUP_CODE 100|10|20|30|40|41|46|71|72|1|3|7|210|220|230|11|21|31|42|43|50|73|44|90|420|421|422|423|424|426|427|428|429|430|431|432|433|434|435|436|437|438|439|45|63|441|75|76|78|79|48|49|50
MTEXT_ENTRY {_space}100{_ret}AcDbMText{_ret}({_space}{MTEXT_GROUP_CODE}{_ret}{_string}?{_ret})+

INSERT_GROUP_CODE 66|2|10|20|30|41|42|43|50|70|71|44|45|210|220|230
INSERT_ENTRY {_space}100{_ret}AcDbBlockReference{_ret}({_space}{INSERT_GROUP_CODE}{_ret}{_string}?{_ret})+

VIEWPORT_GROUP_CODE 100|10|20|30|40|41|68|69|12|22|13|23|14|24|15|25|16|26|36|17|27|37|42|43|44|45|50|51|72|331|90|340|1|281|71|74|110|120|130|111|121|131|112|122|132|345|346|79|146|170|61|332|333|348|292|282|141|142|63|421|431|361|335|343|344|91
VIEWPORT_ENTRY {_space}100{_ret}AcDbViewport{_ret}({_space}{VIEWPORT_GROUP_CODE}{_ret}{_string}?{_ret})+

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

ENTITY_ENTRY_DATA1 {ARC_ENTRY}|{CIRCLE_ENTRY}|{LINE_ENTRY}|{LWPOLYLINE_ENTRY}|{SPLINE_ENTRY}|{TEXT_ENTRY}|{MTEXT_ENTRY}|{VIEWPORT_ENTRY}|{DIMENSION}|{INSERT_ENTRY}
_string [^\n]+

%%
{LINE_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			bool ichar=0;
		/*	while(*yytext!='\0')
			{
				while(*yytext!='\n')
				{
					line+=*yytext;
					ichar++;
					yytext++;
				}
				yytext++;
				ichar=0;
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf.insert(make_pair(mgroup,fgroup_value));
					}
				}
				line="";
				i=!i;
			}*/
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf.insert(make_pair(mgroup,fgroup_value));
					}
				}
				i=!i;
			}
	        return LINE_ENTRY;
		}
{LWPOLYLINE_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			bool ichar=0;
//			dxfvf.clear();
//			vdxfvf.clear();
			vector<float> vf10,vf20;
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100 && mgroup!=91 && mgroup!=10 && mgroup!=20)
					{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf.insert(make_pair(mgroup,fgroup_value));
					}else
					if(mgroup==10||mgroup==20)
					{
						sscanf(line.c_str(),"%f",&fgroup_value);
/*						if(mgroup==10)
						{
							vf10.push_back(fgroup_value);
							vdxfvf.insert(make_pair(mgroup,vf10));
						}
						else
						{
							vf20.push_back(fgroup_value);
							vdxfvf.insert(make_pair(mgroup,vf20));
						}*/
						vdxfvf[mgroup].push_back(fgroup_value);

					}else
					if(mgroup==91)
					{
					}
				}
				i=!i;
			}
	        return LWPOLYLINE_ENTRY;
		}
{HEADER_START}  {
		yy_push_state(_header);
		return HEADER_START;
		}
<_header>{HEADER_VAR}  {
		return HEADER_VAR;
		}
{CLASS_START}  {
		BEGIN(INITIAL);
		return CLASS_START;
		}
{CLASS_ENTRY}  {
		return CLASS_ENTRY;
		}
{SECTION_END}  {
		return SECTION_END;
		}
{TABLE_START}  {
		yy_push_state(_table);
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
{BLOCK_START} {
		 return BLOCK_START;
		}
{BLOCK_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			bool ichar=0;
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						dxfvs[mgroup]=line;
					}
				}
				i=!i;
			}
		 return BLOCK_ENTRY;
		}
{BLOCKEND_ENTRY} {
		return BLOCKEND_ENTRY;
		}
{INSERT_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			bool ichar=0;
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						dxfvs[mgroup]=line;
					}
				}
				i=!i;
			}
			return INSERT_ENTRY;
		}
{ARC_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			bool ichar=0;
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf.insert(make_pair(mgroup,fgroup_value));
					}
				}
				i=!i;
			}
		 return ARC_ENTRY;
		}
{CIRCLE_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			bool ichar=0;
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf.insert(make_pair(mgroup,fgroup_value));
					}
				}
				i=!i;
			}
		 return CIRCLE_ENTRY;
		}
{SPLINE_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
/*			while(*yytext!='\0')
			{
				while(*yytext!='\n')
				{
					line+=*yytext;
					ichar++;
					yytext++;
				}
				yytext++;
				ichar=0;
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					sscanf(line.c_str(),"%f",&fgroup_value);
					if(mgroup!=40 && mgroup!=41&& mgroup!=10 && mgroup!=20 && mgroup!=30 && mgroup!=11 && mgroup!=21 && mgroup!=31)
					{
					dxfvf[mgroup]=fgroup_value;
					}else
					{
				//	vdxfvf[mgroup].push_back(fgroup_value);
					}
				}
				line="";
				i=!i;
			}*/
//			dxfvf.clear();
//			vdxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						sscanf(line.c_str(),"%f",&fgroup_value);
						if(mgroup!=40 && mgroup!=41&& mgroup!=10 && mgroup!=20 && mgroup!=30 && mgroup!=11 && mgroup!=21 && mgroup!=31)
						{
						dxfvf[mgroup]=fgroup_value;
						}else
						{
						vdxfvf[mgroup].push_back(fgroup_value);
						}
					}
				}
				i=!i;
			}
		 return SPLINE_ENTRY;
		}
{TEXT_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvf.clear();
//			dxfvs.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						if(mgroup!=1 && mgroup!=7)
						{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf[mgroup]=fgroup_value;
						}else
						{
						dxfvs[mgroup]=line;
						}
					}
				}
				i=!i;
			}
		 return TEXT_ENTRY;
		}
{MTEXT_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvf.clear();
//			dxfvs.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						if(mgroup!=69 && mgroup!=331 && mgroup!=340 && mgroup!=1 && mgroup!=7 && mgroup!=345 && mgroup!=346 && mgroup!=361 && mgroup!=335 && mgroup!=343 && mgroup!=344 && mgroup!=91)
						{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf[mgroup]=fgroup_value;
						}else
						{
//						sscanf(line.c_str(),"%s",&sgroup_value);
						if(dxfvs[mgroup].size()>0)
							dxfvs[mgroup]+=line;
						else
							dxfvs[mgroup]=line;
						}
					}
				}
				i=!i;
			}
		 return MTEXT_ENTRY;
		}
{VIEWPORT_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvs.clear();
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						if(mgroup!=69 && mgroup!=331 && mgroup!=340 && mgroup!=1 && mgroup!=345 && mgroup!=346 && mgroup!=361 && mgroup!=335 && mgroup!=343 && mgroup!=344 && mgroup!=91)
						{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf[mgroup]=fgroup_value;
						}else
						{
//						sscanf(line.c_str(),"%s",&sgroup_value);
						if(dxfvs[mgroup].size()>0)
							dxfvs[mgroup]+=line;
						else
							dxfvs[mgroup]=line;
						}
					}
				}
				i=!i;
			}
		 return VIEWPORT_ENTRY;
		}
{VPORT_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvs.clear();
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						if(mgroup!=2 && mgroup!=345 && mgroup!=346)
						{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf[mgroup]=fgroup_value;
						}else
						{
							dxfvs[mgroup]=line;
						}
					}
				}
				i=!i;
			}
		 return VPORT_ENTRY;
		}
{APPID_ENTRY} {
		 return APPID_ENTRY;
}
{BLOCK_RECORD_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvs.clear();
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						dxfvs[mgroup]=line;
					}
				}
				i=!i;
			}
		 return BLOCK_RECORD_ENTRY;
}
{DIMSTYLE_ENTRY} {
		 return DIMSTYLE_ENTRY;
}
{LAYER_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvs.clear();
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						if(mgroup!=2 && mgroup!=6 && mgroup!=390 && mgroup!=347)
						{
						sscanf(line.c_str(),"%f",&fgroup_value);
						dxfvf[mgroup]=fgroup_value;
						}else
						{
							dxfvs[mgroup]=line;
						}
					}
				}
				i=!i;
			}
		 return LAYER_ENTRY;
}
{LTYPE_ENTRY} {
		 return LTYPE_ENTRY;
}
{STYLE_ENTRY} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvs.clear();
//			dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=100)
					{
						dxfvs[mgroup]=line;
					}
				}
				i=!i;
			}
		 return STYLE_ENTRY;
}
{UCS_ENTRY} {
		 return UCS_ENTRY;
}
{VIEW_ENTRY} {
		 return VIEW_ENTRY;
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
		 return ENTITY_START;
		}
{ENTITY_CMN_GROUP} {
			char* cc=yytext;
			string scc(cc);
			stringstream _full(scc);
			string line;
			int mgroup=-1;
			float fgroup_value;
			string sgroup_value;
			bool i=false;
			int ichar=0;
//			dxfvs.clear();
	//		dxfvf.clear();
			while(getline(_full,line))
			{
				if(!i)
				sscanf(line.c_str(),"%d",&mgroup);
				else
				{
					if(mgroup!=0)
					{
							dxfvs[mgroup]=line;
					}
				}
				i=!i;
			}
		 return ENTITY_CMN_GROUP;
		}
%%