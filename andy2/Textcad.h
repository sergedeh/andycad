// TextCad.h: interface for the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
#define AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_
#include "Vector.h"	// Added by ClassView
#include "Rectangle.h"	// Added by ClassView
#include "figure.h"	// Added by ClassView
#include <map>
#include <functional>
#include "Bezier.h"
#include "txted.h"

#include <memory>
#include <vector>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

class CTextCad : public CLine  
{
public:
//	DWORD CALLBACK EditStreamCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	void Stream(CArchive& ar, BOOL bSelection);
	void Serialize(CArchive& ar);
	void setLcolor(CDC *hdc,COLORREF color,COLORREF bcolor);
	void getfont(CHARFORMAT& cf);
	void setpara(CString l);
	bool WndVisible();
	void setWnd(CWnd* cad);
	// Test-drawing generator: create the edit control (by drawing once), set
	// the text, and make the first `boldRedChars` characters bold red.
	void setTextForTest(CDC* hdc, const CString& s, int boldRedChars);
	// Editing in the RichEdit box: beginEdit shows it upright over the text
	// with an OK button; commitEdit (OK) keeps the changes and puts the text
	// back on the canvas; cancelEdit (click outside, Escape) restores the
	// content from when the box opened.
	void beginEdit();
	void commitEdit();
	void cancelEdit();
	bool isEditing() const { return m_editing; }
	// Scale mode: false = scaling the box re-wraps the text (paragraph text,
	// the existing behaviour); true = the characters scale with the box
	// (artistic text). Saved with the text.
	void setScaleCharacters(bool on);
	bool scaleCharacters() const { return m_scaleChars; }
	// Direct2D path: DirectWrite glyphs at the projected anchors, oriented by
	// the text box itself (so rotation and mirroring follow the figure).
	// Available once the text has been laid out and is not being edited.
	bool canRender() const override;
	void draw(acr::IRenderer* r) override;
	void drawOverlay(CDC* hdc) override;
	// Convert to curves: one filled CLine per character (glyph outlines,
	// holes kept), in world space, matching what is on screen. Empty if the
	// text has not been laid out yet.
	std::vector<CFigure*> toCurves(CDC* hdc);
	// How many times the character layout has been rebuilt (tests).
	int layoutCount() const { return m_layout.count; }
	void assign(CDC* hdc, CVector p);
	CFigure* generateCopy();
	void Rotate(int sens,CVector prevpoint,CVector postpoint);
	void editobj(CDC* hdc);
	void editobj(CVector point);
	void edittext();
	void setText(CString vtext,CDC* hdc);
	void draw3D(CDC *hdc);
	void InitZoom();
	void updatecopy();
	CFont* getFont();
	bool inRegion(CVector point);
	void assign(CDC *hdc,CVector p,CString s,CHARFORMAT* _cf=NULL);
	void openfile(CFile &file,CDC* hdc);
	void savefile(CFile &file);
	void savefiledxf(CStdioFile& file);
	void setFStyle(FSTYLE* _fstyle);
	CPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf);
	bool PtinRegion(CVector point);
	void drawTrans(CDC *hdc);
	void translate(CWnd *wnd,CDC *hdc, CVector prevpos, CVector postpos);
	void draw(CDC *hdc);
	void create(CVector pos);
//	CRect getTextrec(CDC *hdc);
	void getTextrec(CWnd* wnd,CDC *hdc);
	void initL();
	void setMove(bool b,CVector point);
	void FillText();
	bool getCharge();
	void setPtsBegin(CVector point);
	bool draw(bool fPrevLine,CDC *hdc, CVector point);
	CRectangle* getRectangle();
	CTextCad();
	CTextCad(CFile &file,CDC* hdc);
	virtual ~CTextCad();

private:

	CVector vecsepos;
	int iter,biter,sbiter,seiter,liter;
	vector<bool> vecbe;
	vector<CString*> stk;
	vector<CString*>::iterator is;
	map<int,CString> mstr;
	CRectangle rec;
	bool fPrevB;
	bool selmode;
	CFont* pfont,*tfont;
	TEXTMETRIC textmet;
	CString *str;
	static CWnd * wd;

	CVector curspos;
	//vector<vector<CVector*> >::iterator liter;

    CTxtED* rich;
	// The OK button belongs to this text only: copies start without one.
	struct OkButtonHolder {
		CTextOkButton* p = nullptr;
		OkButtonHolder() = default;
		OkButtonHolder(const OkButtonHolder&) {}
		OkButtonHolder& operator=(const OkButtonHolder&) { return *this; }
		~OkButtonHolder() { if (p) { if (p->m_hWnd) p->DestroyWindow(); delete p; } }
	} m_ok;
	CStringA m_editSnapshot;      // RTF when the edit box opened (for cancel)
	bool m_editing = false;
	bool m_scaleChars = false;
	// The text's own frame: x along the box's 0->1 edge, "down" along
	// m_frameSign times its 0->3 edge. Fixed when the text is first laid out
	// and saved, so transforms (including mirroring) carry it with the box.
	// 0 = not known yet.
	int m_frameSign = 0;
	double m_charScale = 1.0;     // box scale since layout (artistic mode)
	void bakeCharScale();
	// Glyphs for the current view; M = view logical -> device (+0.5).
	void buildGlyphs(const acr::Mat3& M, std::vector<acr::GlyphDraw>& out);
	void positionOkButton();
	void hideEditor();
	void redrawCanvas();
	// Character layout cache for draw3D (see Textcad.cpp).
	struct LayoutCache {
		struct Glyph {
			char ch = 0; long line = 0;
			CPoint dev;        // edit-box position (layout input)
			CVector off;       // world offset from the text origin, unrotated
			CVector anchor;    // world position: figure geometry, transformed by UpdateMesh
			CPoint placed;     // text-space position when the anchor was placed
			LOGFONT lf = {}; COLORREF color = 0;
		};
		bool anchorsValid = false;
		double boxW0 = 0, boxH0 = 0;   // world box size when anchors were placed
		double sgnY = 1;               // glyph "down" relative to the box's 0->3 edge
		bool anchorsMoved = false;      // a transform moved the anchors since placing
		POINT placedReal[3] = {}, placedText[3] = {};
		CPoint placedProj;
		double placedScale = 0;
		int count = 0;
		CVector anchorOrigin;  // mesh vertex 0 when the anchors were placed
		CStringA rtf;
		double wn = 0, hn = 0;     // box size / projectedScale() at layout
		double editorScale = 0;    // projectedScale() the edit box's fonts match
		int richMapMode = MM_TEXT;
		bool valid = false;
		std::vector<Glyph> glyphs;
		double scale = 0;          // projectedScale() when laid out
		double fontAngle = 1e300;
		double fontScale = 0;
		std::vector<std::shared_ptr<void>> fonts;   // HFONTs, rotated
	} m_layout;
	CStringA streamRichRtf();
	static double projectedScale();
	void UpdateMesh() override;
	CVector ppvlo;
	int width; 
	float z_prev,u_prev;
		CBezier bz;
		CString mtext;
	FSTYLE* fstyle;
	int i, j;
};

#endif // !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
