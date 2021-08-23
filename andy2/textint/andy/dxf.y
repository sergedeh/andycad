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
CDC * dxfHdc;
bool dxfBlock=false;
CVector dxfcv;
int _token=-1;
int nbline=0,nbspline=0;
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
%token TABLE_CMN_GROUP TABLE_START TABLE_ENTRY CLASS_ENTRY CLASS_START error2
%token BLOCK_START BLOCK_ENTRY BLOCKEND_ENTRY
%token APPID_ENTRY BLOCK_RECORD_ENTRY DIMSTYLE_ENTRY LAYER_ENTRY LTYPE_ENTRY STYLE_ENTRY UCS_ENTRY VIEW_ENTRY VPORT_ENTRY
%token ENTITY_CMN_GROUP ENTITY_START LINE_GROUP_CODE
%token DIMENSION_ENTRY ALDIMENSION_ENTRY LRDIMENSION_ENTRY RDIMENSION_ENTRY ANDIMENSION_ENTRY ODIMENSION_ENTRY
%token ARC_ENTRY CIRCLE_ENTRY LINE_ENTRY SPLINE_ENTRY TEXT_ENTRY MTEXT_ENTRY VIEWPORT_ENTRY LWPOLYLINE_ENTRY INSERT_ENTRY
%error-verbose 

%% /* Grammar rules and actions follow */

input: /*empty*/
		|input HEADER 
		|input CLASSES 
		|input TABLES 
		|input BLOCKS
		|input ENTITIES

HEADER: HEADER_START {_out="Catching an Header Start \n";
							 yyerror(yytext);} HEADER_VARS SECTION_END {_out="Catching a Section End \n";
																				yyerror(yytext);}
HEADER_VARS: /*empty*/
			 |HEADER_VAR {_out="Catching an Header variable \n";
							yyerror(yytext);} HEADER_VARS
CLASSES: CLASS_START {_out="Catching a Class Start \n";
							 yyerror(yytext);} CLASS_ENTRIES SECTION_END {_out="Catching a Section End \n";
																				yyerror(yytext);}
CLASS_ENTRIES: /*empty*/
				|CLASS_ENTRY {_out="Catching a Class Entry \n";
							yyerror(yytext);} CLASS_ENTRIES
TABLES:  TABLE_START {_out="Catching a Table Start \n";
							 yyerror(yytext);} TABLE_ENTRIES SECTION_END {_out="Catching a Table Section End \n";
							 yyerror(yytext);}
		    { 
			}
TABLE_ENTRY1:  TABLE_ENTRY {_out="Catching a Table Entry \n";
							 yyerror(yytext);} TABLE_ENTRY_DATA TABLE_END {_out="Catching a Table End \n";
							 yyerror(yytext);}
TABLE_ENTRIES: TABLE_ENTRY1
				|TABLE_ENTRIES TABLE_ENTRY1 

TABLE_ENTRY_DATA:	/*empty*/
					|TABLE_CMN_GROUP {_out="Catching a Table Common Entry Data \n";
							 yyerror(yytext);} TABLE_ENTRY_DATA1 {_out="Catching a Table Entry Data \n";
							 yyerror(yytext);}
					|TABLE_ENTRY_DATA TABLE_CMN_GROUP {_out="Catching a Table Common Entry Data \n";
							 yyerror(yytext);} TABLE_ENTRY_DATA1 {_out="Catching a Table Entry Data \n";
							 yyerror(yytext);} 
TABLE_ENTRY_DATA1:	APPID_ENTRY|
					BLOCK_RECORD_ENTRY{
								string _text=dxfvs[2];
								if(!dxfBlock)
									dxfpDoc->m_objects->AddBlock(_text);
								dxfvs.clear();
					}|
					DIMSTYLE_ENTRY|
					LAYER_ENTRY{
								string _text=dxfvs[2];
								int layer_status=(dxfvf[70]==4)?1:0;
								int layer_color=dxfvf[62];
								int layer_lineweight=dxfvf[370];
								string layer_linetype=dxfvs[6];
								if(!dxfBlock)
									dxfpDoc->m_objects->AddLayer(_text,layer_status,layer_color,layer_linetype,layer_lineweight);
								dxfvf.clear();
								dxfvs.clear();
					}|
					LTYPE_ENTRY|
					STYLE_ENTRY {
								string _text=dxfvs[2];
								float fixed_height=atof(dxfvs[40].c_str());
								float width_factor=atof(dxfvs[41].c_str());
								string _font=dxfvs[3];
								dxfpDoc->m_objects->AddTextStyle(_text,_font,fixed_height,width_factor);
								dxfvs.clear();
					}|
					UCS_ENTRY|
					VIEW_ENTRY|
					VPORT_ENTRY {
								if(dxfvs[2]=="*Active")
								{
								string _text=dxfvs[1];
								CVector vo_wcs(dxfvf[10],dxfvf[20],dxfvf[30]);
								CVector vo_dcs(dxfvf[12],dxfvf[22]);
								CVector viewdir_dcs(dxfvf[16],dxfvf[26],dxfvf[36]);
								float zoom_pc=dxfvf[72];
								CVector vo_ucs(dxfvf[110],dxfvf[120],dxfvf[130]);
								CVector vox_ucs(dxfvf[111],dxfvf[121],dxfvf[131]);
								CVector voy_ucs(dxfvf[112],dxfvf[122],dxfvf[132]);

								int paper_width=dxfvf[40];
								int paper_height=dxfvf[41];
								if(!dxfBlock)
									dxfpDoc->m_objects->AddViewport(dxfHdc,vo_wcs,vo_dcs,vo_ucs,vox_ucs,voy_ucs,zoom_pc,paper_width,paper_height);
								dxfvf.clear();
								}
					}

BLOCKS:  BLOCK_START {
					 _token=BLOCK_START;
					_out="Catching a Block Start \n";
							 yyerror(yytext);} BLOCK_ENTRIES SECTION_END {
																			if(dxfBlock) YYACCEPT;
																			_out="Catching a Block Section End \n";
																			yyerror(yytext);}
BLOCK_ENTRIES: BLOCK_ENTRY1
				|BLOCK_ENTRIES BLOCK_ENTRY1 
BLOCK_ENTRY1: BLOCK_ENTRY {
							dxfvs.clear();
							_out="Catching a Block Entry \n";
							 yyerror(yytext);} BLOCKEND_ENTRY {_out="Catching a Block End Entry \n";
							 yyerror(yytext);}
			 |BLOCK_ENTRY {
								CVector vo(atof(dxfvs[10].c_str()),atof(dxfvs[20].c_str()),atof(dxfvs[30].c_str()));
								string _text=dxfvs[2];
								string _layer=dxfvs[8];
								string _handle=dxfvs[5];
								dxfpDoc->m_objects->AddBlock2(_text,_layer,_handle,vo);
								dxfvs.clear();
			 
			 _out="Catching a Block Entry \n";
							 yyerror(yytext);} ENTITY_ENTRIES BLOCKEND_ENTRY {_out="Catching a Block End Entry\n";
							 yyerror(yytext);}
ENTITY_ENTRIES: ENTITY_ENTRY1
				|ENTITY_ENTRIES ENTITY_ENTRY1 
ENTITY_ENTRY1: ENTITY_CMN_GROUP {
							 string layer_name=dxfvs[8];
                             dxfpDoc->m_objects->setCurrentLayer(layer_name);//dxfpvec);
							 dxfvs.clear();

							 _out="Catching an Entity Common Entry \n";
							 yyerror(yytext);} ENTITY_ENTRY_DATA1 {_out="Catching an Entity Entry Data \n";
							 yyerror(yytext);}
DIMENSION : DIMENSION_ENTRY ALDIMENSION_ENTRY|
			DIMENSION_ENTRY LRDIMENSION_ENTRY|
			DIMENSION_ENTRY RDIMENSION_ENTRY|
			DIMENSION_ENTRY ANDIMENSION_ENTRY|
			DIMENSION_ENTRY ODIMENSION_ENTRY
ENTITY_ENTRY_DATA1: /*empty*/
					|ARC_ENTRY{
									CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
									float r=dxfvf[40];
									float start_a=(dxfvf[50]*2*pi)/360;
									CVector vstart=vo+polarc(r,start_a);
									float end_a=dxfvf[51];
									end_a=(end_a<dxfvf[50])?360+end_a:end_a;
									end_a=(end_a*2*pi)/360;;
									CVector vend=vo+polarc(r,end_a);
									float angle=end_a-start_a;
									dxfpDoc->m_objects->AddArc(vo,vstart,angle);//dxfpvec);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									dxfvf.clear();
					}
					|CIRCLE_ENTRY{
									CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
									float r=dxfvf[40];
									dxfpDoc->m_objects->AddCircle(vo,r);//dxfpvec);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									dxfvf.clear();
					}
					|LINE_ENTRY { 
									CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
									CVector ve(dxfvf[11],dxfvf[21],dxfvf[31]);
									vector<CVector> vg;
									vg.push_back(vo);
									vg.push_back(ve);
									dxfpDoc->m_objects->AddLine(vg);//dxfpvec);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									dxfvf.clear();
								
								nbline++;
								}
					|LWPOLYLINE_ENTRY { 
								int nb_cpts=dxfvf[90];
								vector<CVector> vg;
								for(int i=0;i<nb_cpts;i++)
								{
									CVector vo(vdxfvf[10][i],vdxfvf[20][i]);
									vg.push_back(vo);
								}
									vdxfvf[10].clear();
									vdxfvf[20].clear();

									dxfpDoc->m_objects->AddLine(vg);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									vdxfvf.clear();
									dxfvf.clear();
								
							}
					|SPLINE_ENTRY{
								int nb_cpts=dxfvf[73];
								vector<CVector> vg,vg1;
								for(int i=0;i<nb_cpts;i++)
								{
									CVector vo(vdxfvf[10][i],vdxfvf[20][i],vdxfvf[30][i]);
									vg.push_back(vo);
								}
								int nb_knts=dxfvf[72];
								vector<float> fvg;
								for(i=0;i<nb_knts;i++)
								{
									fvg.push_back(vdxfvf[40][i]);
								}
									vdxfvf[10].clear();
									vdxfvf[20].clear();
									vdxfvf[30].clear();
									vdxfvf[40].clear();
									dxfpDoc->m_objects->AddSpline2(vg,fvg,false,dxfHdc);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									vdxfvf.clear();
									dxfvf.clear();
									nbspline++;
								
					
					}
					|VIEWPORT_ENTRY{
								if(_token==ENTITY_START)
								{
								string _text=dxfvs[1];
								CVector vo_wcs(dxfvf[10],dxfvf[20],dxfvf[30]);
								CVector vo_dcs(dxfvf[12],dxfvf[22]);
								CVector viewdir_dcs(dxfvf[16],dxfvf[26],dxfvf[36]);
								float zoom_pc=dxfvf[72];
								CVector vo_ucs(dxfvf[110],dxfvf[120],dxfvf[130]);
								CVector vox_ucs(dxfvf[111],dxfvf[121],dxfvf[131]);
								CVector voy_ucs(dxfvf[112],dxfvf[122],dxfvf[132]);

								int paper_width=dxfvf[40];
								int paper_height=dxfvf[41];
								dxfpDoc->m_objects->AddViewport(dxfHdc,vo_wcs,vo_dcs,vo_ucs,vox_ucs,voy_ucs,zoom_pc,paper_width,paper_height);
								dxfvf.clear();
								}
					}
					|MTEXT_ENTRY{
								string _text=dxfvs[1];
								CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
								int attachpoint=dxfvf[71];
								dxfpDoc->m_objects->AddText(dxfHdc,vo,_text,dxfvf[40],dxfvs[7]);
								if(_token==BLOCK_START)
								{
								dxfpDoc->m_objects->AddToBlock();
								}
								dxfvf.clear();
								dxfvs.clear();
								
					
					}
					|TEXT_ENTRY{
								string _text=dxfvs[1];
								CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
								int attachpoint=dxfvf[71];
								dxfpDoc->m_objects->AddText(dxfHdc,vo,_text,dxfvf[40],dxfvs[7]);
								if(_token==BLOCK_START)
								{
								dxfpDoc->m_objects->AddToBlock();
								}
								dxfvf.clear();
								dxfvs.clear();
					}
					|INSERT_ENTRY {
								CVector vo(atof(dxfvs[10].c_str()),atof(dxfvs[20].c_str()),atof(dxfvs[30].c_str()));
								string _text=dxfvs[2];
								CVector vscale(atof(dxfvs[41].c_str()),atof(dxfvs[42].c_str()),atof(dxfvs[43].c_str()));
								float rot_angle=atof(dxfvs[50].c_str());
								CVector col_row_count(atof(dxfvs[70].c_str()),atof(dxfvs[71].c_str()));
								CVector col_row_spacing(atof(dxfvs[44].c_str()),atof(dxfvs[45].c_str()));
								dxfpDoc->m_objects->AddBlock3(_text,rot_angle,vscale,vo,col_row_count,col_row_spacing);
								if(_token==BLOCK_START)
								{
								dxfpDoc->m_objects->AddToBlock();
								}
								dxfvs.clear();
					} |DIMENSION

ENTITIES:  ENTITY_START {_out="Catching an Entity Start \n";
							 yyerror(yytext);
							 _token=ENTITY_START;
						} ENTITY_ENTRIES SECTION_END {_out="Catching a Block Section End \n";
														yyerror(yytext);
														_token=-1;
													 }

%%       