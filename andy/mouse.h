// Mouse.h: interface for the CMouse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSE_H__4E8FB4E7_7D24_42F2_8F6B_BA036CF5B3DE__INCLUDED_)
#define AFX_MOUSE_H__4E8FB4E7_7D24_42F2_8F6B_BA036CF5B3DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMouse  
{
public:
	CPoint getPrevPos();
	void setPrevPos(CPoint point);
	bool getLBdownStatus();
	void setLBdown(bool LBdownstate);
	bool getMove();
	void setMove(bool moveStatus);
	CPoint getPostPos();
	void setPostPos(CPoint point);
	CMouse();
	virtual ~CMouse();

private:
	static bool LBdown;
	static bool move;
	static CPoint Prevposition;
	static CPoint Postposition;
};

#endif // !defined(AFX_MOUSE_H__4E8FB4E7_7D24_42F2_8F6B_BA036CF5B3DE__INCLUDED_)
