// Pattern.cpp: implementation of the CPattern class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Pattern.h"
#include "BArrowp.h"
#include "mainfrm.h"
#include "ximage.h"
	

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void * CPattern::pPatternD;
int  CPattern::iter=0;


BEGIN_MESSAGE_MAP(CPattern, CDialogBar)
	//{{AFX_MSG_MAP(CPattern)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
//    ON_BN_CLICKED(2520,OnLButtonarr1)
 //   ON_BN_CLICKED(2521,OnLButtonarr2)
    ON_BN_CLICKED(2510,OnLButtonpal)
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPattern::CPattern()
{
	arrow1.setorient(true);arrow2.setorient(false);
//	pColorD=new
	if(iter==0)
	pPatternD=this;
	iter++;
	
	bmp=new CBitmap;
	but=new CRecPattern[50];

		itpos=0;
}

CPattern::~CPattern()
{
 	delete []but;
	delete bmp;
}

int CPattern::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CFileFind finder;
/*	bool bWorking=finder.FindFile("texture/*.bmp");
	nsize=0;
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CFile file(finder.GetFilePath(),CFile::modeRead);
	CString s=finder.GetFilePath();
	fvec.push_back(s);

//	but[nsize].setBitmap(paty[nsize],finder.GetFilePath());
	nsize++;
	}*/
	bool bWorking=finder.FindFile("texture/*.PNG");
	nsize=0;
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CFile file(finder.GetFilePath(),CFile::modeRead);
	CString s=finder.GetFilePath();
	fvec.push_back(s);

//	but[nsize].setBitmap(paty[nsize],finder.GetFilePath());
	nsize++;
	}
	finder.Close();
	for(int i=0;i<nsize;i++)
		{
			CBitmap* pattern= new CBitmap;

			CDC *hdc=GetDC();	
			CDC* phdc=new CDC;
			phdc->CreateCompatibleDC(hdc);
			pattern->CreateCompatibleBitmap(hdc,25,25);
			CBitmap* o=phdc->SelectObject(pattern);

//			CImagex texture(hdc->GetSafeHdc(),fvec[i].GetBuffer(10));
			CxImage texture;
			texture.Load(fvec[i],CXIMAGE_FORMAT_PNG);
			CBrush br1(RGB(255,255,255));
			phdc->FillRect(CRect(0,0,25,25),&br1);
//			phdc->Rectangle(CRect(0,0,25,25));
			bool b=texture.Draw(phdc->GetSafeHdc(),0,0,20,20);
			phdc->SelectObject(o);
			delete phdc;
			ReleaseDC(hdc);
			paty.push_back(pattern);
			but[i].setBitmap(paty[i],fvec[i]);
		}
	if(nsize>=4) nsize=4;
   

   CRect rec;
	GetClientRect(rec);
	CPaintDC dc(this);

	int cx=lpCreateStruct->cx;
	int cy=lpCreateStruct->cy;
	int unit=25;


	
	CRect v1(0,0,0,0);
	arrow1.Create(NULL,WS_VISIBLE|
			WS_CHILD|BS_FLAT|BS_ICON,v1,this,2520);
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON6);
	arrow1.SetIcon(icon);
	arrow1.GetIcon();


	st1.Create(NULL,WS_VISIBLE|
			WS_CHILD|BS_PUSHBUTTON|BS_FLAT|BS_ICON,v1,this,2510);
	icon = AfxGetApp()->LoadIcon(IDI_ICON4);
	st1.SetIcon(icon);
	st1.GetIcon();
	
	CRect v(0,0,0,0);
	int j=0;
	for(i=0;i<nsize;i++)
	{
		but[i].CreateEx(NULL,_T("BUTTON"),NULL,WS_VISIBLE|
			WS_CHILD,v,this,4600+i,NULL);
		but[i].v=v;
	}
	nbcolbut=nsize;
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

void CPattern::OnLButtonarr1() 
{

		if(itpos+nsize<fvec.size())
		{
			itpos++;
//		it=itpos%256;
		
		int j=1;

		for(int i=itpos;i<min(itpos+nsize,fvec.size())-1/*(itpos-1)+min(nbcolbut,nsize)*/;i++)
		{
			but[j-1].patsource=fvec[i];
			but[j-1].pattern=paty[i];
			but[j-1].Invalidate();
			j++;
		}
		}

}



void CPattern::OnLButtonarr2() 
{

		if(itpos>0) itpos--;
		int j=0;
		for(int i=itpos;i<min(itpos+nsize,fvec.size())/*(itpos+1)+min(nbcolbut,nsize)*/;i++)
		{
			but[j].patsource=fvec[i];
			but[j].pattern=paty[i];
			but[j].Invalidate();
			j++;
		}


}

void CPattern::OnLButtonpal() 
{
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	CCadView * pv=(CCadView*)mg->GetActiveView();
	pv->Unfill();
}


CSize CPattern::CalcDynamicLayout( int nLength, DWORD dwMode )
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





void CPattern::OnPaint() 
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
		but[i].patsource=fvec[i];
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
		but[i].patsource=fvec[i];
		but[i].pattern=paty[i];
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


void CPattern::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	bDisableIfNoHndler = FALSE;
	CDialogBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);
}
