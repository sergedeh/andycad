%{
#include <malloc.h>
#define alloc _alloc
#include <stdio.h>
#include <vector>
using namespace std;


vector<CVector> pvec;
vector<float> fvec;
CString out,com;
CCadDoc* pDoc;
CCadView *pView;
CVector cv;


yyerror (char* s)  /* Called by yyparse on error */
{
 // printf ("%s\n", s);
  CString f(s);
  out+=f;
}
/*	|line			{
								com="First Point:";
								pvec.clear();
					}
	|spline			{
								com="First Point:";
								pvec.clear();
					}
	|rect			{
								com="First Corner:";
								pvec.clear();
					}
	|circle			{
								com="Center Point:";
								pvec.clear();
					}

	|arc			{
								com="Center Point:";
								pvec.clear();
					}
	|MODEL			{
								com="Size of the Model Space (X,Y):";
								pvec.clear();
					}

	|ZOOM		 	{
								com="Enter a scale factor:";
						}
	|numexpr ',' numexpr 	{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case MODEL:
							{
							com="Command: ";
							pDoc->m_objects->setPage(CSize(f1,f2));
							pView->Invalidate(TRUE);
							vi.pop();
							break;
							}
							default:
							;
							}
							}
							else
								out+="No command has been entered";
						}
	|numexpr  			{
	                        float f1=vf.front();vf.pop();
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case ZOOM:
							{
							com="Command: ";
							pDoc->m_objects->setzoomrat(f1);
							pView->Invalidate(TRUE);
							vi.pop();
							break;
							}
							case circle:
							{
							if(pvec.size()==1)
							{
							pDoc->m_objects->AddCircle(pvec[0],f1);
							vi.pop();
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
							}
							break;
							}
							default:
							;
							}
							}
							else
								out+="No command has been entered";
						}

	|point			{
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case line:
							{
							com="Next Point:";
							pDoc->m_objects->addLine2(pvec);
							if(pvec.size()>1)
								pView->Invalidate(TRUE);
							break;
							}
							case spline:
							{
							com="Next Point:";
							pDoc->m_objects->AddSpline2(pvec);
							cv=pvec.back();
							if(pvec.size()>1)
								pView->Invalidate(TRUE);
							break;
							}
							case rect:
							{
							if(pvec.size()<1)
							{
							com="Next Corner:";
							}
							if(pvec.size()>1){
							pDoc->m_objects->AddRectangle(pvec[0],pvec[1]);
							vi.pop();
							pView->Invalidate(TRUE);
							}
							break;
							}
							case circle:
							{
							if(pvec.size()==1)
								com="Radius:";
							break;
							}
							default:
							;
							}
							}
							else
								out+="No command has been entered";

					}
						
						
						*/


%}
/* Digital electronic simulator. */
%token _delete line rect circle qline ellipse arc spline spline2 MOVE MOVENODE ROTATE text
%token object help num OFFSET BREAKCURVE SCALE SCALE2 ANGCOPY POLARCOPY ARRAYCOPY LOOKAT ROTATECAM
%token SWIVEL ZOOM MOVECAM MOVETO MOVENODETO error2 MODEL

%% /* Grammar rules and actions follow */

input:    /* empty */
        | input _Line

_Line:      { 
							while(!vi.empty())
								vi.pop();
							pvec.clear();
			}
        | expr     { 
							
					}
expr:
	 _delete numexpr	{
	                        int f1=vf.front();vf.pop();
							pDoc->m_objects->Delete(f1);
							pView->Invalidate(TRUE);
						}
	 |line point points	{
//							if(pvec.size()==2)
								pDoc->m_objects->AddLine(pvec);
							cv=pvec.back();
							pvec.clear(); 
							pView->Invalidate(TRUE);
						}
    |rect point point	{ 
							pDoc->m_objects->AddRectangle(pvec[0],pvec[1]);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|circle point numexpr   { 
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->AddCircle(pvec[0],f1);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|qline point points { 
							out+="I am drawing a qline\r\n";
						}
	|ellipse point numexpr  { 
							out+="I am drawing an ellipse\r\n";
						}
	|arc point point numexpr		{ 
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->AddArc(pvec[0],pvec[1],f1);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|arc point numexpr numexpr numexpr		{ 
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
							pDoc->m_objects->AddArc(pvec[0],f1,f2,f3);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|arc point point point		{ 
							pDoc->m_objects->AddArc(pvec[0],pvec[1],pvec[2]);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|arc point point		{ 
							pDoc->m_objects->AddArc(pvec[0],pvec[1]);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|spline point points { 
							pDoc->m_objects->AddSpline(pvec);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|spline2 point points knots { 
							pDoc->m_objects->AddSpline2(pvec,fvec,false);
							cv=pvec.back();
							pvec.clear();
							fvec.clear();
							pView->Invalidate(TRUE);
						}
	|MOVE point			{
							pDoc->m_objects->Move(NULL,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|MOVETO point			{
							pDoc->m_objects->MoveTo(NULL,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|MOVENODE point numexpr	{
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->Move(NULL,f1,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|MOVENODETO point numexpr	{
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->MoveTo(NULL,f1,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|ROTATE point numexpr numexpr  {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
							pDoc->m_objects->rotate(f1,f2,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|ROTATE numexpr	numexpr		{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotate(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|SCALE point numexpr numexpr  {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->scale(f1,f2,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|SCALE numexpr numexpr			{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->scale(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|SCALE2 numexpr			{
	                        float f1=vf.front();vf.pop();
						    pDoc->m_objects->copy2(f1);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|OFFSET numexpr			{
	                        float f1=vf.front();vf.pop();
						    pDoc->m_objects->Offset(f1);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|BREAKCURVE numexpr numexpr{			
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->AddBreak(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						}

	|ANGCOPY point numexpr numexpr numexpr numexpr
						{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
						    pDoc->m_objects->copyRSparam2(NULL,f1,f2,f3,f4,false,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|POLARCOPY point numexpr numexpr numexpr numexpr
						{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
						    pDoc->m_objects->copyRSparam2(NULL,f1,f2,f3,f4,true,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						}
	|ARRAYCOPY numexpr numexpr numexpr numexpr numexpr numexpr
						{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
	                        float f5=vf.front();vf.pop();
	                        float f6=vf.front();vf.pop();
						    pDoc->m_objects->pastearray(NULL,true,f1,f3,f2,f4,f5,f6);
							pView->Invalidate(TRUE);
						}
	|LOOKAT point point	{
						}
	|ROTATECAM numexpr numexpr	{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotatecam(f1,f2);
							pView->Invalidate(TRUE);
						}
	|SWIVEL numexpr numexpr	{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotatecam(f1,f2,true);
							pView->Invalidate(TRUE);
						}
	|MOVECAM point	{
						    pDoc->m_objects->translatecam(pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
					}
	|ZOOM numexpr	{
	                        float f1=vf.front();vf.pop();
						    pDoc->m_objects->setzoomrat(f1);
							pvec.clear();
							pView->Invalidate(TRUE);
					}
	|help			{
						out+= " For more information about a specific command, type [help command-name] \r\n\r\n";
						out+= " line \t\t display a multiline object \r\n";
						out+= " rect \t\t display a rectangle object \r\n";
						out+= " circle \t\t display a circle object \r\n";
						out+= " arc \t\t display a arc object \r\n";
						out+= " spline \t\t display a spline object \r\n";
						out+= " move \t\t move an object by a vector \r\n";
						out+= " moveto \t\t move an object (its barycentre) to a specific point. \r\n";
						out+= " movenode \t move an object node by a vector \r\n";
						out+= " movenodeto \t move an object node to a specific point. \r\n";
						out+= " rotate \t\t rotate an object by an angle. \r\n";
						out+= " scale \t\t scale an object by a scaling (X,Y) factor. \r\n";
						out+= " scale2 \t\t scale an object by a unique scaling factor. \r\n";
						out+= " offset \t\t offset an object by a distance. \r\n";
						out+= " breakcurve \t\t break a curve from a distance1 to a distance 2. \r\n";
						out+= " angcopy \t\t copy an object at specific angle around a center point. \r\n";
						out+= " polarcopy \t copy an object at specific angle around a center point. \r\n";
						out+= " arraycopy \t copy an object at specific X,Y distance. \r\n";
						out+= " lookat \t\t direct the camera to look at a specific point. \r\n";
						out+= " rotatecam \t rotate the camera by a specific angle. \r\n";
						out+= " swivel \t\t swivel the camera by specific distance in X,Y. \r\n";
						out+= " movecam \t move the camera to a specific point. \r\n\r\n";
						out+= " For more informtion on tools, see the command line reference in the online help. \r\n";

					}
	|help line			{
						out+= " Display a multiline object \r\n\r\n";
						out+= " line point point [point...]  \r\n\r\n";
						out+= " example 1: Draw a multiline from (0,0) to (150,0) then (500,0) \r\n\r\n";
						out+= " line <0,0> <150,150> <500,0>  \r\n\r\n";
					}
	|help rect			{
						out+= " Display a rectangle object \r\n\r\n";
						out+= " rect point point  \r\n\r\n";
						out+= " example 1: Draw a Rectangle from (0,0) to (500,500) \r\n\r\n";
						out+= " rect <0,0> <500,0>  \r\n\r\n";
					}
	|help circle			{
						out+= " Display a circle object \r\n\r\n";
						out+= " circle point radius  \r\n\r\n";
						out+= " example 1: Draw a circle with center (0,0) and radius 500 \r\n\r\n";
						out+= " circle <0,0> 500  \r\n\r\n";
					}
	|help arc			{
						out+= " Display an arc object \r\n\r\n";
						out+= " arc point point angle  \r\n\r\n";
						out+= " example 1: Draw an arc from (0,0) to (500,0) with 300deg \r\n\r\n";
						out+= " arc <0,0> <500,0> 300  \r\n\r\n";
						out+= " example 2: Draw an arc with passing through (0,0), (500,0) and (300,200) \r\n\r\n";
						out+= " arc <0,0> <500,0> <300,200>  \r\n\r\n";
						out+= " example 3: Draw an arc with passing through (0,0) and <500,0> \r\n\r\n";
						out+= " arc <0,0> <500,0> \r\n\r\n";
					}
	|help spline			{
						out+= " Display a spline object \r\n\r\n";
						out+= " spline point point [point...]  \r\n\r\n";
						out+= " example 1: Draw a spline from (0,0) to (150,300) then (500,0) \r\n\r\n";
						out+= " spline <0,0> <150,300> <500,0>  \r\n\r\n";
					}
	|help MOVE			{
						out+= " Move an object by a vector \r\n\r\n";
						out+= " move point   \r\n\r\n";
						out+= " example 1: Move a selected object by a vector (200,300) \r\n\r\n";
						out+= " move <200,300>  \r\n\r\n";
					}
	|help MOVETO	{
						out+= " Move an object (its barycentre) to a specific point. \r\n\r\n";
						out+= " moveto point  \r\n\r\n";
						out+= " example 1: Move a selected object by to the point (200,300) \r\n\r\n";
						out+= " moveto <200,300>  \r\n\r\n";
					}
	|help MOVENODE			{
						out+= " Move an object node by a vector \r\n\r\n";
						out+= " movenode point nodenumber  \r\n\r\n";
						out+= " example 1: Move the 1st node of a selected object by a vector (200,300) \r\n\r\n";
						out+= " movenode <200,300> 1  \r\n\r\n";
					}
	|help MOVENODETO			{
						out+= " Move an object node to a specific point. \r\n\r\n";
						out+= " movenodeto point nodenumber  \r\n\r\n";
						out+= " example 1: Move the 1st node of a selected object to the point (200,300) \r\n\r\n";
						out+= " movenodeto <200,300> 1  \r\n\r\n";
					}
	|help ROTATE			{
						out+= " Rotate an object by an angle. \r\n\r\n";
						out+= " rotate point xangle yangle  \r\n\r\n";
						out+= " rotate xangle yangle  \r\n\r\n";
						out+= " example 1: rotate the selected object by 300deg \r\n\r\n";
						out+= " rotate 300 0  \r\n\r\n";
						out+= " example 2: rotate the selected object by 300deg with a center of rotation at <0,0>\r\n\r\n";
						out+= " rotate <0,0> 300 0  \r\n\r\n";
					}
	|help SCALE			{
						out+= " Scale an object by a scaling (X,Y) factor. \r\n\r\n";
						out+= " scale point xscale yscale  \r\n\r\n";
						out+= " scale xscale yscale  \r\n\r\n";
						out+= " scale2 xyscale  \r\n\r\n";
						out+= " example 1: scale the selected object by 2 \r\n\r\n";
						out+= " scale 2 1  \r\n\r\n";
						out+= " example 2: scale the selected object by 2 with a center of scale at <0,0>\r\n\r\n";
						out+= " scale <0,0> 2 1  \r\n\r\n";
						out+= " example 3: scale the selected object by 1.5 \r\n\r\n";
						out+= " scale2 1.5   \r\n\r\n";
						}
	|help OFFSET			{
						out+= " Offset an object by a distance . \r\n\r\n";
						out+= " offset distance  \r\n\r\n";
						out+= " example 1: offset the selected object by 50 \r\n\r\n";
						out+= " offset 50  \r\n\r\n";
						}
	|help BREAKCURVE			{
						out+= " Breack a curve selected from a distance 1 to a distance 2 . \r\n\r\n";
						out+= " breakcurve distance1 distance2  \r\n\r\n";
						out+= " example 1: break the selected curve from 100 to 150 \r\n\r\n";
						out+= " breakcurve 100 150  \r\n\r\n";
					}
	|help ANGCOPY			{
						out+= " Copy an object at specific angle around a center point. \r\n\r\n";
						out+= " angcopy u1 u2 u3 u4  \r\n\r\n";
						out+= " example 1: angular copy the selected object around the center <0,0> by 45deg with 4 copies \r\n\r\n";
						out+= " angcopy <0,0> 45 4 1 0  \r\n\r\n";
					}
	|help POLARCOPY			{
						out+= " Copy an object at specific angle around a center point. \r\n\r\n";
						out+= " polarcopy u1 u2 u3 u4  \r\n\r\n";
						out+= " example 1: polar copy the selected object around the center <0,0> by 45deg with 4 copies \r\n\r\n";
						out+= " polarcopy <0,0> 45 4 1 0  \r\n\r\n";
					}
	|help ARRAYCOPY			{
						out+= " Copy an object at specific X,Y distance. \r\n\r\n";
						out+= " arraycopy u1 u2 u3 u4 u5 u6  \r\n\r\n";
						out+= " example 1: array copy the selected object on 3 rows sparated by 200 units and 4 columns separated by 400 units \r\n\r\n";
						out+= " arraycopy 3 200 4 400 1 0  \r\n\r\n";
					}
	|help LOOKAT			{
						out+= " Direct the camera to look at a specific point. \r\n\r\n";
						out+= " lookat point  \r\n\r\n";
					}
	|help ROTATECAM			{
						out+= " Rotate the camera by a specific angle. \r\n\r\n";
						out+= " rotatecam xangle yangle  \r\n\r\n";
						out+= " example 1: Rotate the camera by 45 deg \r\n\r\n";
						out+= " rotatecam 45 0  \r\n\r\n";
					}
	|help SWIVEL			{
						out+= "Swivel the camera by specific distance in X,Y. \r\n\r\n";
						out+= " swivel xangle yangle  \r\n\r\n";
						out+= " example 1: Swivel the camera by 45 deg \r\n\r\n";
						out+= " swivel 45 0  \r\n\r\n";
					}
	|help MOVECAM			{
						out+= " Move the camera to a specific point \r\n\r\n";
						out+= " movecam point  \r\n\r\n";
						out+= " example 1: Move the camera by the vector (200,300) \r\n\r\n";
						out+= " movecam 200 300  \r\n\r\n";
					}
	|help ZOOM			{
						out+= " Zoom the camera to a specific ratio \r\n\r\n";
						out+= " zoom 1.5  \r\n\r\n";
						out+= " example 1: Zoom the camera by 2 \r\n\r\n";
						out+= " zoom 2  \r\n\r\n";
					}

knots:
	  '[' nums ']'			{ 
//	                                float f1=vf.front();vf.pop();
	//                                float f2=vf.front();vf.pop();
									while(!vf.empty())
									{
		                                float f1=vf.front();vf.pop();
										fvec.push_back(f1);
									}
								}
point:
	  '<'numexpr','numexpr'>'			{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									pvec.push_back(CVector(f1,f2));
									int n=pvec.size();
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);
								}
	  |'<'numexpr','numexpr','numexpr'>'	{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
	                                float f3=vf.front();vf.pop();
									pvec.push_back(CVector(f1,f2,f3));
									int n=pvec.size();
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);
								}
	  |numexpr'<'numexpr				{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=(f2*pi)/180;
									CVector v = polarc(f1,f2);
									pvec.push_back(v);
									int n=pvec.size();
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);
								}

	  |'@' point				{ 
									int n=pvec.size();
									CVector v;
								    pDoc->m_objects->getfromPoint(pvec);
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);									
								}
points:  point
		|point points
nums:  numexpr
		|numexpr nums
numexpr: 
		num				{ 
	                //                float f1=vf.front();vf.pop();
						//			vf.push(f1);
								}
	 | 'pi'						{
									vf.push(pi);
								}
	 | numexpr '/' numexpr				{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1/f2;
									vf.push(f2);
								}
	 | numexpr '*' numexpr				{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1*f2;
									vf.push(f2);
								}
	 | numexpr '-' numexpr				{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1-f2;
									vf.push(f2);
								}
	 | numexpr '+' numexpr				{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1+f2;
									vf.push(f2);
								}


%%       