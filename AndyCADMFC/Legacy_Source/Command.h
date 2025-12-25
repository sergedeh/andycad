// Command.h: interface for the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMAND_H__339DC1DB_3420_4608_936A_E39C1C49523E__INCLUDED_)
#define AFX_COMMAND_H__339DC1DB_3420_4608_936A_E39C1C49523E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommand  
{
public:
	virtual void Execute() {};
	CCommand();
	virtual ~CCommand();

};

#endif // !defined(AFX_COMMAND_H__339DC1DB_3420_4608_936A_E39C1C49523E__INCLUDED_)
