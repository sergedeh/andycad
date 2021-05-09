%option noyywrap
%{
#include <io.h>
#include <queue>
#include <deque>
#define isatty _isatty

using namespace std;
typedef queue<float> fqueue;
typedef queue<int> iqueue;

fqueue vf;
iqueue vi;

%}
error2 "error2"
MODEL "model"
_delete "delete"
line "line"
rect "rect"
circle "circle"
qline "qline"
ellipse "ellipse"
arc "arc"
text "text"
spline "spline"
spline2 "spline2"
BREAKCURVE "breakcurve"
OFFSET "offset"
MOVECAM "movecam"
ZOOM "zoom"
SWIVEL "ivel"
ROTATECAM "rotatecam"
LOOKAT "lookat"
ARRAYCOPY "arraycopy"
POLARCOPY "polarcopy"
ANGCOPY "angcopy"
SCALE2 "scale2"
SCALE "scale"
ROTATE "rotate"
MOVENODE "movenode"
MOVE "move"
MOVENODETO "movenodeto"
MOVETO "moveto"
help "help"
DIGIT [0-9]
sign "-"|"+"
num {sign}?{DIGIT}+|{sign}?{DIGIT}+"."{DIGIT}*
mchar "\n"|"["|"]"|"<"|">"|","|"@"|"/"|"+"|"-"|"*"|"pi"|"?"

%%
{BREAKCURVE}  {
        vi.push(BREAKCURVE);
		return BREAKCURVE;
		}
{OFFSET}  {
        vi.push(OFFSET);
		return OFFSET;
		}
{_delete}  {
        vi.push(_delete);
		return _delete;
		}
{line}  {
        vi.push(line);
		return line;
		}
{MODEL}  {
        vi.push(MODEL);
		return MODEL;
		}
{qline}  {
        vi.push(qline);
		return qline;
		}
{rect}  {
        vi.push(rect);
		return rect;
		}
{text}  {
        vi.push(text);
		return text;
		}
{ellipse}  {
		return ellipse;
		}
{circle}  {
        vi.push(circle);
		return circle;
		}
{spline} {
        vi.push(spline);
		 return spline;
		}
{spline2} {
        vi.push(spline2);
		 return spline2;
		}
{arc} {
         vi.push(arc);
		 return arc;
		}
{help} {
		return help;
		}
{num}	{
			vf.push(atof(yytext));
			return num;
		}
{mchar}   {
		  return *yytext;
		}		
{MOVECAM} {return MOVECAM;}
{ZOOM} {
	        vi.push(ZOOM);
			return ZOOM;}
{SWIVEL} {return SWIVEL;}
{ROTATECAM} {return ROTATECAM;}
{LOOKAT} {return LOOKAT;}
{ARRAYCOPY} {return ARRAYCOPY;}
{POLARCOPY} {return POLARCOPY;}
{ANGCOPY} {return ANGCOPY;}
{SCALE2} {return SCALE2;}
{SCALE} {return SCALE;}
{ROTATE} {return ROTATE;}
{MOVENODE} {return MOVENODE;}
{MOVE} {return MOVE;}
{MOVENODETO} {return MOVENODETO;}
{MOVETO} {return MOVETO;}
{error2}    ;
[\r\n\x20]+ ;
.        {
			return error2;
		   }

%%