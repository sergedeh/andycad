// ColorD.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "mainfrm.h"
#include "ColorD.h"
#include "cadview.h"
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
void * CColorD::pColorD;
int  CColorD::iter=0;

// Standard colors
RGBQUAD ms_StdColors[] = {
    { 0x00, 0x00, 0x00, 0 },  // System palette - first 10 colors
    { 0x80, 0x00, 0x00, 0 },
    { 0x00, 0x80, 0x00, 0 },
    { 0x80, 0x80, 0x00, 0 },
    { 0x00, 0x00, 0x80, 0 },
    { 0x80, 0x00, 0x80, 0 },
    { 0x00, 0x80, 0x80, 0 },
    { 0xC0, 0xC0, 0xC0, 0 },
    { 0xC0, 0xDC, 0xC0, 0 },
    { 0xA6, 0xCA, 0xF0, 0 },

    { 0x2C, 0x00, 0x00, 0 },
    { 0x56, 0x00, 0x00, 0 },
    { 0x87, 0x00, 0x00, 0 },
    { 0xC0, 0x00, 0x00, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0x00, 0x2C, 0x00, 0 },
    { 0x2C, 0x2C, 0x00, 0 },
    { 0x56, 0x2C, 0x00, 0 },
    { 0x87, 0x2C, 0x00, 0 },
    { 0xC0, 0x2C, 0x00, 0 },
    { 0xFF, 0x2C, 0x00, 0 },
    { 0x00, 0x56, 0x00, 0 },
    { 0x2C, 0x56, 0x00, 0 },
    { 0x56, 0x56, 0x00, 0 },
    { 0x87, 0x56, 0x00, 0 },
    { 0xC0, 0x56, 0x00, 0 },
    { 0xFF, 0x56, 0x00, 0 },
    { 0x00, 0x87, 0x00, 0 },
    { 0x2C, 0x87, 0x00, 0 },
    { 0x56, 0x87, 0x00, 0 },
    { 0x87, 0x87, 0x00, 0 },
    { 0xC0, 0x87, 0x00, 0 },
    { 0xFF, 0x87, 0x00, 0 },
    { 0x00, 0xC0, 0x00, 0 },
    { 0x2C, 0xC0, 0x00, 0 },
    { 0x56, 0xC0, 0x00, 0 },
    { 0x87, 0xC0, 0x00, 0 },
    { 0xC0, 0xC0, 0x00, 0 },
    { 0xFF, 0xC0, 0x00, 0 },
    { 0x00, 0xFF, 0x00, 0 },
    { 0x2C, 0xFF, 0x00, 0 },
    { 0x56, 0xFF, 0x00, 0 },
    { 0x87, 0xFF, 0x00, 0 },
    { 0xC0, 0xFF, 0x00, 0 },
    { 0xFF, 0xFF, 0x00, 0 },
    { 0x00, 0x00, 0x2C, 0 },
    { 0x2C, 0x00, 0x2C, 0 },
    { 0x56, 0x00, 0x2C, 0 },
    { 0x87, 0x00, 0x2C, 0 },
    { 0xC0, 0x00, 0x2C, 0 },
    { 0xFF, 0x00, 0x2C, 0 },
    { 0x00, 0x2C, 0x2C, 0 },
    { 0x2C, 0x2C, 0x2C, 0 },
    { 0x56, 0x2C, 0x2C, 0 },
    { 0x87, 0x2C, 0x2C, 0 },
    { 0xC0, 0x2C, 0x2C, 0 },
    { 0xFF, 0x2C, 0x2C, 0 },
    { 0x00, 0x56, 0x2C, 0 },
    { 0x2C, 0x56, 0x2C, 0 },
    { 0x56, 0x56, 0x2C, 0 },
    { 0x87, 0x56, 0x2C, 0 },
    { 0xC0, 0x56, 0x2C, 0 },
    { 0xFF, 0x56, 0x2C, 0 },
    { 0x00, 0x87, 0x2C, 0 },
    { 0x2C, 0x87, 0x2C, 0 },
    { 0x56, 0x87, 0x2C, 0 },
    { 0x87, 0x87, 0x2C, 0 },
    { 0xC0, 0x87, 0x2C, 0 },
    { 0xFF, 0x87, 0x2C, 0 },
    { 0x00, 0xC0, 0x2C, 0 },
    { 0x2C, 0xC0, 0x2C, 0 },
    { 0x56, 0xC0, 0x2C, 0 },
    { 0x87, 0xC0, 0x2C, 0 },
    { 0xC0, 0xC0, 0x2C, 0 },
    { 0xFF, 0xC0, 0x2C, 0 },
    { 0x00, 0xFF, 0x2C, 0 },
    { 0x2C, 0xFF, 0x2C, 0 },
    { 0x56, 0xFF, 0x2C, 0 },
    { 0x87, 0xFF, 0x2C, 0 },
    { 0xC0, 0xFF, 0x2C, 0 },
    { 0xFF, 0xFF, 0x2C, 0 },
    { 0x00, 0x00, 0x56, 0 },
    { 0x2C, 0x00, 0x56, 0 },
    { 0x56, 0x00, 0x56, 0 },
    { 0x87, 0x00, 0x56, 0 },
    { 0xC0, 0x00, 0x56, 0 },
    { 0xFF, 0x00, 0x56, 0 },
    { 0x00, 0x2C, 0x56, 0 },
    { 0x2C, 0x2C, 0x56, 0 },
    { 0x56, 0x2C, 0x56, 0 },
    { 0x87, 0x2C, 0x56, 0 },
    { 0xC0, 0x2C, 0x56, 0 },
    { 0xFF, 0x2C, 0x56, 0 },
    { 0x00, 0x56, 0x56, 0 },
    { 0x2C, 0x56, 0x56, 0 },
    { 0x56, 0x56, 0x56, 0 },
    { 0x87, 0x56, 0x56, 0 },
    { 0xC0, 0x56, 0x56, 0 },
    { 0xFF, 0x56, 0x56, 0 },
    { 0x00, 0x87, 0x56, 0 },
    { 0x2C, 0x87, 0x56, 0 },
    { 0x56, 0x87, 0x56, 0 },
    { 0x87, 0x87, 0x56, 0 },
    { 0xC0, 0x87, 0x56, 0 },
    { 0xFF, 0x87, 0x56, 0 },
    { 0x00, 0xC0, 0x56, 0 },
    { 0x2C, 0xC0, 0x56, 0 },
    { 0x56, 0xC0, 0x56, 0 },
    { 0x87, 0xC0, 0x56, 0 },
    { 0xC0, 0xC0, 0x56, 0 },
    { 0xFF, 0xC0, 0x56, 0 },
    { 0x00, 0xFF, 0x56, 0 },
    { 0x2C, 0xFF, 0x56, 0 },
    { 0x56, 0xFF, 0x56, 0 },
    { 0x87, 0xFF, 0x56, 0 },
    { 0xC0, 0xFF, 0x56, 0 },
    { 0xFF, 0xFF, 0x56, 0 },
    { 0x00, 0x00, 0x87, 0 },
    { 0x2C, 0x00, 0x87, 0 },
    { 0x56, 0x00, 0x87, 0 },
    { 0x87, 0x00, 0x87, 0 },
    { 0xC0, 0x00, 0x87, 0 },
    { 0xFF, 0x00, 0x87, 0 },
    { 0x00, 0x2C, 0x87, 0 },
    { 0x2C, 0x2C, 0x87, 0 },
    { 0x56, 0x2C, 0x87, 0 },
    { 0x87, 0x2C, 0x87, 0 },
    { 0xC0, 0x2C, 0x87, 0 },
    { 0xFF, 0x2C, 0x87, 0 },
    { 0x00, 0x56, 0x87, 0 },
    { 0x2C, 0x56, 0x87, 0 },
    { 0x56, 0x56, 0x87, 0 },
    { 0x87, 0x56, 0x87, 0 },
    { 0xC0, 0x56, 0x87, 0 },
    { 0xFF, 0x56, 0x87, 0 },
    { 0x00, 0x87, 0x87, 0 },
    { 0x2C, 0x87, 0x87, 0 },
    { 0x56, 0x87, 0x87, 0 },
    { 0x87, 0x87, 0x87, 0 },
    { 0xC0, 0x87, 0x87, 0 },
    { 0xFF, 0x87, 0x87, 0 },
    { 0x00, 0xC0, 0x87, 0 },
    { 0x2C, 0xC0, 0x87, 0 },
    { 0x56, 0xC0, 0x87, 0 },
    { 0x87, 0xC0, 0x87, 0 },
    { 0xC0, 0xC0, 0x87, 0 },
    { 0xFF, 0xC0, 0x87, 0 },
    { 0x00, 0xFF, 0x87, 0 },
    { 0x2C, 0xFF, 0x87, 0 },
    { 0x56, 0xFF, 0x87, 0 },
    { 0x87, 0xFF, 0x87, 0 },
    { 0xC0, 0xFF, 0x87, 0 },
    { 0xFF, 0xFF, 0x87, 0 },
    { 0x00, 0x00, 0xC0, 0 },
    { 0x2C, 0x00, 0xC0, 0 },
    { 0x56, 0x00, 0xC0, 0 },
    { 0x87, 0x00, 0xC0, 0 },
    { 0xC0, 0x00, 0xC0, 0 },
    { 0xFF, 0x00, 0xC0, 0 },
    { 0x00, 0x2C, 0xC0, 0 },
    { 0x2C, 0x2C, 0xC0, 0 },
    { 0x56, 0x2C, 0xC0, 0 },
    { 0x87, 0x2C, 0xC0, 0 },
    { 0xC0, 0x2C, 0xC0, 0 },
    { 0xFF, 0x2C, 0xC0, 0 },
    { 0x00, 0x56, 0xC0, 0 },
    { 0x2C, 0x56, 0xC0, 0 },
    { 0x56, 0x56, 0xC0, 0 },
    { 0x87, 0x56, 0xC0, 0 },
    { 0xC0, 0x56, 0xC0, 0 },
    { 0xFF, 0x56, 0xC0, 0 },
    { 0x00, 0x87, 0xC0, 0 },
    { 0x2C, 0x87, 0xC0, 0 },
    { 0x56, 0x87, 0xC0, 0 },
    { 0x87, 0x87, 0xC0, 0 },
    { 0xC0, 0x87, 0xC0, 0 },
    { 0xFF, 0x87, 0xC0, 0 },
    { 0x00, 0xC0, 0xC0, 0 },
    { 0x2C, 0xC0, 0xC0, 0 },
    { 0x56, 0xC0, 0xC0, 0 },
    { 0x87, 0xC0, 0xC0, 0 },
    { 0xFF, 0xC0, 0xC0, 0 },
    { 0x00, 0xFF, 0xC0, 0 },
    { 0x2C, 0xFF, 0xC0, 0 },
    { 0x56, 0xFF, 0xC0, 0 },
    { 0x87, 0xFF, 0xC0, 0 },
    { 0xC0, 0xFF, 0xC0, 0 },
    { 0xFF, 0xFF, 0xC0, 0 },
    { 0x00, 0x00, 0xFF, 0 },
    { 0x2C, 0x00, 0xFF, 0 },
    { 0x56, 0x00, 0xFF, 0 },
    { 0x87, 0x00, 0xFF, 0 },
    { 0xC0, 0x00, 0xFF, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0x00, 0x2C, 0xFF, 0 },
    { 0x2C, 0x2C, 0xFF, 0 },
    { 0x56, 0x2C, 0xFF, 0 },
    { 0x87, 0x2C, 0xFF, 0 },
    { 0xC0, 0x2C, 0xFF, 0 },
    { 0xFF, 0x2C, 0xFF, 0 },
    { 0x00, 0x56, 0xFF, 0 },
    { 0x2C, 0x56, 0xFF, 0 },
    { 0x56, 0x56, 0xFF, 0 },
    { 0x87, 0x56, 0xFF, 0 },
    { 0xC0, 0x56, 0xFF, 0 },
    { 0xFF, 0x56, 0xFF, 0 },
    { 0x00, 0x87, 0xFF, 0 },
    { 0x2C, 0x87, 0xFF, 0 },
    { 0x56, 0x87, 0xFF, 0 },
    { 0x87, 0x87, 0xFF, 0 },
    { 0xC0, 0x87, 0xFF, 0 },
    { 0xFF, 0x87, 0xFF, 0 },
    { 0x00, 0xC0, 0xFF, 0 },
    { 0x2C, 0xC0, 0xFF, 0 },
    { 0x56, 0xC0, 0xFF, 0 },
    { 0x87, 0xC0, 0xFF, 0 },
    { 0xC0, 0xC0, 0xFF, 0 },
    { 0xFF, 0xC0, 0xFF, 0 },
    { 0x2C, 0xFF, 0xFF, 0 },
    { 0x56, 0xFF, 0xFF, 0 },
    { 0x87, 0xFF, 0xFF, 0 },
    { 0xC0, 0xFF, 0xFF, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },
    { 0x11, 0x11, 0x11, 0 },
    { 0x18, 0x18, 0x18, 0 },
    { 0x1E, 0x1E, 0x1E, 0 },
    { 0x25, 0x25, 0x25, 0 },
    { 0x2C, 0x2C, 0x2C, 0 },
    { 0x34, 0x34, 0x34, 0 },
    { 0x3C, 0x3C, 0x3C, 0 },
    { 0x44, 0x44, 0x44, 0 },
    { 0x4D, 0x4D, 0x4D, 0 },
    { 0x56, 0x56, 0x56, 0 },
    { 0x5F, 0x5F, 0x5F, 0 },
    { 0x69, 0x69, 0x69, 0 },
    { 0x72, 0x72, 0x72, 0 },
    { 0x7D, 0x7D, 0x7D, 0 },
    { 0x92, 0x92, 0x92, 0 },
    { 0x9D, 0x9D, 0x9D, 0 },
    { 0xA8, 0xA8, 0xA8, 0 },
    { 0xB4, 0xB4, 0xB4, 0 },
    { 0xCC, 0xCC, 0xCC, 0 },
    { 0xD8, 0xD8, 0xD8, 0 },
    { 0xE5, 0xE5, 0xE5, 0 },
    { 0xF2, 0xF2, 0xF2, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },

    { 0xFF, 0xFB, 0xF0, 0 },  // System palette - last 10 colors
    { 0xA0, 0xA0, 0xA4, 0 },
    { 0x80, 0x80, 0x80, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0x00, 0xFF, 0x00, 0 },
    { 0xFF, 0xFF, 0x00, 0 },
    { 0x00, 0x00, 0xFF, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0x00, 0xFF, 0xFF, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },
};

/////////////////////////////////////////////////////////////////////////////
// CColorD

CColorD::CColorD()
{
	arrow1.setorient(true);arrow2.setorient(false);
//	pColorD=new
	if(iter==0)
	pColorD=this;
	iter++;

/*	LPLOGPALETTE lplogpal;
	HBITMAP  hbm;
	HRSRC hres;
	HGLOBAL hdata;
	

	if(
		(
		hres=::FindResource(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP3),RT_BITMAP)
		)!=NULL &&
		(
		hdata=::LoadResource(::AfxGetResourceHandle(),hres)
		)!=NULL
		)
	{
		lpbm=(LPBITMAPINFO)::LockResource(hdata);
	}
	switch(lpbm->bmiHeader.biBitCount)
	{
	case 1:
		{
			nsize=2;
			break;
		}
	case 4:
		{
			nsize=16;
			break;
		}
	case 8:
		{
			nsize=256;
			break;
		}
	default:
		{
			nsize=0;
		}
	}

	
*/
	bmp=new CBitmap;
	but=new CRecColor[50];

/*	pLP = (LOGPALETTE*) new BYTE[sizeof(LOGPALETTE)+(nsize-1)*sizeof(PALETTEENTRY)];
	pLP->palVersion = 0x300;
	pLP->palNumEntries = nsize;

	for (int i=0; i<nsize; i++) {
    pLP->palPalEntry[i].peRed =lpbm->bmiColors[i].rgbRed;
    pLP->palPalEntry[i].peGreen=lpbm->bmiColors[i].rgbGreen;
    pLP->palPalEntry[i].peBlue=lpbm->bmiColors[i].rgbBlue;
    pLP->palPalEntry[i].peFlags = NULL;
	}
	
	palette.CreatePalette (pLP);
//	::FreeResource(hdata);
*/
/*	WNDCLASSEX clx,wc;
	GetClassInfoEx(NULL,"CToolbar",&wc);
//	clx.cbSize=sizeof(WNDCLASS);
	clx.lpfnWndProc=NULL;
	clx.lpszClassName="ColorToolBar";
	clx.style=wc.style;
	clx.hIcon = wc.hIcon; 
    clx.hCursor = wc.hCursor; 
	clx.cbWndExtra=0;
	clx.hbrBackground=wc.hbrBackground;

	RegisterClassEx(&clx);*/
	itpos=0;
}

CColorD::~CColorD()
{
	delete []but;
	delete bmp;
}


BEGIN_MESSAGE_MAP(CColorD, CDialogBar)
	//{{AFX_MSG_MAP(CColorD)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
//    ON_BN_CLICKED(2520,OnLButtonarr1)
 //   ON_BN_CLICKED(2521,OnLButtonarr2)
    ON_BN_CLICKED(2510,OnLButtonpal)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorD message handlers





/*LRESULT __stdcall MainWndProc(HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
	return 0;
}*/

int CColorD::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;


	CRect rec;
	GetClientRect(rec);
	CPaintDC dc(this);

/*	HBITMAP hbmp=::CreateDIBitmap(dc.GetSafeHdc(),&lpbm->bmiHeader,CBM_INIT,
						  (LPSTR)lpbm+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*nsize,
						  lpbm,DIB_RGB_COLORS);
	bmp->Attach(hbmp);
	
	dcmemory.CreateCompatibleDC(&dc);
	dcmemory.SelectObject(bmp);
	dcmemory.SelectPalette(&palette,FALSE);
	
*/
	int cx=lpCreateStruct->cx;
	int cy=lpCreateStruct->cy;
	int unit=25;


	
//	CRect v1(5,5,unit,unit);
	CRect v1(0,0,0,0);
	arrow1.Create(NULL,WS_VISIBLE|
			WS_CHILD|BS_FLAT|BS_ICON,v1,this,2520);
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON6);
	arrow1.SetIcon(icon);
	arrow1.GetIcon();

///	v1.left+=21;
//	v1.right+=21;

	st1.Create(NULL,WS_VISIBLE|
			WS_CHILD|BS_PUSHBUTTON|BS_FLAT|BS_ICON,v1,this,2510);
	icon = AfxGetApp()->LoadIcon(IDI_ICON4);
	st1.SetIcon(icon);
	st1.GetIcon();
	
//	int nbcolbut=cx/unit;
	CRect v(0,0,0,0);
	int j=0;
	nsize=15;
	for(int i=0;i<=nsize;i++)
	{
	//	v.left+=21;
	//	v.right+=21;
		but[i].CreateEx(NULL,_T("BUTTON"),NULL,WS_VISIBLE|
			WS_CHILD,v,this,4500+i,NULL);
		but[i].color=RGB(ms_StdColors[i].rgbRed,ms_StdColors[i].rgbGreen,ms_StdColors[i].rgbBlue);//PALETTEINDEX(i);
		but[i].v=v;

	}
	nbcolbut=nsize;
	//v.left+=21;
	//v.right+=21;
	st2.Create(NULL,WS_VISIBLE|
			WS_CHILD|BS_PUSHBUTTON|BS_FLAT|BS_ICON,v,this,2510);
	st2.SetIcon(icon);
	st2.GetIcon();

//	v.left+=21;
//	v.right+=21;
	arrow2.Create(NULL,WS_VISIBLE|
			WS_CHILD|BS_PUSHBUTTON|BS_FLAT|BS_ICON,v,this,2521);
	icon = AfxGetApp()->LoadIcon(IDI_ICON5);
	arrow2.SetIcon(icon);
	arrow2.GetIcon();
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CColorD::OnLButtonarr1() 
{

		if(itpos+nsize<255)
		{
		itpos++;
//		it=itpos%256;
		int j=1;

		for(int i=itpos;i<=min(itpos+nbcolbut,255)/*(itpos-1)+min(nbcolbut,nsize)*/;i++)
		{
			but[j-1].color=RGB(ms_StdColors[i].rgbRed,ms_StdColors[i].rgbGreen,ms_StdColors[i].rgbBlue);//(pLP->palPalEntry[i].peBlue<<16)|(pLP->palPalEntry[i].peGreen<<8)|pLP->palPalEntry[i].peRed;
			but[j-1].Invalidate();
			j++;
		}
		}

}



void CColorD::OnLButtonarr2() 
{

		if(itpos>0) itpos--;
		int j=0;
		for(int i=itpos;i<=min(itpos+nbcolbut,255)/*(itpos+1)+min(nbcolbut,nsize)*/;i++)
		{
			but[j].color=RGB(ms_StdColors[i].rgbRed,ms_StdColors[i].rgbGreen,ms_StdColors[i].rgbBlue);//(pLP->palPalEntry[i].peBlue<<16)|(pLP->palPalEntry[i].peGreen<<8)|pLP->palPalEntry[i].peRed;
			but[j].Invalidate();
			j++;
		}


}

void CColorD::OnLButtonpal() 
{
/*	if(coldial.DoModal()==IDOK)
	{
		COLORREF* col=coldial.GetSavedCustomColors();
		int j=0;
		for(int i=itpos;i<=itpos+15;i++)
		{
			pLP->palPalEntry[i].peRed= col[j]&0x0000ff;
			pLP->palPalEntry[i].peGreen=(col[j]&0x00ff00)>>8;
			pLP->palPalEntry[i].peBlue=(col[j]&0xff0000)>>16;
			j++;
		}
		palette.SetPaletteEntries(0,256,pLP->palPalEntry);

		Invalidate();
		j=0;
		for(i=0;i<=15;i++)
		{
//		but[j].color=(pLP->palPalEntry[i].peBlue<<16)|(pLP->palPalEntry[i].peGreen<<8)|pLP->palPalEntry[i].peRed;
		but[i].Invalidate();
		}
	}*/
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	CCadView * pv=(CCadView*)mg->GetActiveView();
	pv->Unfill();
}


CSize CColorD::CalcDynamicLayout( int nLength, DWORD dwMode )
{

/*	CSize size;
	CMainFrame *ptrWnd;
	CRect rect;

	ptrWnd=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	ptrWnd->GetClientRect(rect);
	if((dwMode & LM_VERTDOCK) || (dwMode & LM_HORZDOCK))
	{
		size.cx=(dwMode & LM_HORZ) ? m_sizeDefault.cx:m_sizeDefault.cy;
		size.cy=(dwMode & LM_HORZ) ? m_sizeDefault.cy:rect.Height();//m_sizeDefault.cx;

		return size;
	}*/
	return CDialogBar::CalcDynamicLayout(nLength, dwMode);
}





void CColorD::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rec;
	GetClientRect(rec);

/*	CPalette *oldpal=dc.SelectPalette(&palette,FALSE);
	dc.RealizePalette();

	dc.StretchBlt(0,0,rec.Width(),rec.Height(),&dcmemory,0,0,lpbm->bmiHeader.biWidth,lpbm->bmiHeader.biHeight,SRCCOPY);
*/


 if(rec.Width()<rec.Height())
	{
	int cx=rec.Width();
	int cy=rec.Height();
	int unit=30;


	
	CRect v1(5,5,unit,unit);
	arrow1.MoveWindow(v1);
	
	v1.left=5;
	v1.right=30;
	v1.bottom+=26;
	v1.top+=26;
	st1.MoveWindow(v1);
	
	
	nbcolbut=(cy-2*unit)/unit;
	//CRect v(5,5,3*unit,3*unit);
	CRect v=v1;
	int j=0;
	for(int i=0;i<min(nbcolbut,nsize);i++)
	{
		v.left=5;
		v.right=30;
		v.bottom+=26;
		v.top+=26;
		but[i].color=RGB(ms_StdColors[i].rgbRed,ms_StdColors[i].rgbGreen,ms_StdColors[i].rgbBlue);//PALETTERGB(pLP->palPalEntry[i].peRed,pLP->palPalEntry[i].peGreen,pLP->palPalEntry[i].peBlue);//PALETTEINDEX(i);
		but[i].v=v;
		but[i].MoveWindow(v);
		j=j+5;
	}
	v.left=5;
	v.right=30;
	v.bottom+=26;
	v.top+=26;
	st2.MoveWindow(v);

	v.left=5;
	v.right=30;
	v.bottom+=26;
	v.top+=26;
	arrow2.MoveWindow(v);

 }else
 if(rec.Width()>rec.Height())
	{
	int cx=rec.Width();
	int cy=rec.Height();
	int unit=30;

	
	CRect v1(5,5,unit,unit);
	arrow1.MoveWindow(v1);
	
	v1.left+=26;
	v1.right+=26;
	st1.MoveWindow(v1);
	
	
	nbcolbut=(cx-2*unit)/unit;
	//CRect v(3*unit,3*unit,5,5);
	CRect v=v1;
	int j=0;
	for(int i=0;i<min(nbcolbut,nsize);i++)
	{
		v.left+=26;
		v.right+=26;
		but[i].color=RGB(ms_StdColors[i].rgbRed,ms_StdColors[i].rgbGreen,ms_StdColors[i].rgbBlue);//PALETTEINDEX(i);
		but[i].v=v;
		but[i].MoveWindow(v);
		j=j+5;
	}
	v.left+=26;
	v.right+=26;
	st2.MoveWindow(v);

	v.left+=26;
	v.right+=26;
	arrow2.MoveWindow(v);

	}
	// TODO: Add your message handler code here
	
	// Do not call CDialogBar::OnPaint() for painting messages
}


void CColorD::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	bDisableIfNoHndler = FALSE;
	CDialogBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);
}



