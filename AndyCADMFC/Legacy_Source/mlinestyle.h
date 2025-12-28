// MLinestyle.h: interface for the CMLinestyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MLINESTYLE_H__C12EFDD3_97BF_40DF_9CA4_261722FA0CAA__INCLUDED_)
#define AFX_MLINESTYLE_H__C12EFDD3_97BF_40DF_9CA4_261722FA0CAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MENU1	0
#define MENU2	1
#define MENU3	2
#define MENU4	3
#define MENU5	4
#define MENU6	5

class CMLinestyle : public CMenu  
{

protected:
	CBitmap m_bmp1;
	CBitmap m_bmp2;
	CBitmap m_bmp3;
	CBitmap m_bmp4;
public:
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	virtual void MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct );;
	CMLinestyle();
	virtual ~CMLinestyle();

};

#endif // !defined(AFX_MLINESTYLE_H__C12EFDD3_97BF_40DF_9CA4_261722FA0CAA__INCLUDED_)
