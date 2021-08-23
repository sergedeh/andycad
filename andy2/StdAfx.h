// pch.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F2173DBD_A611_44D8_B708_3C8934D40CA1__INCLUDED_)
#define AFX_STDAFX_H__F2173DBD_A611_44D8_B708_3C8934D40CA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0600	// Change this to the appropriate value to target other versions of Windows.
#endif						


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxdocob.h>
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxpriv.h>
#include <afxtempl.h>
//#include "memdc.h"

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "C:\Users\Administrator\source\repos\andycad\andy\TipDlg.h"
//#include <htmlhelp.h>
#include <algorithm>
#include <iterator>


const double pi=3.14159265358979;
#define WIDTHBYTES(bits) ((((bits)+31)/32)*4)

#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
#include <Afxctl.h>




static const GUID CATID_ANDYCAD_ADDINS =
{ 0x35434C80, 0x2FD1, 0x47B3, { 0x91, 0x05, 0x12, 0x6F, 0xC7, 0x34,0xE7, 0x0E } };

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module


class CCadModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
	
};
extern CCadModule _Module;
#include <atlcom.h>
#include <atlctl.h>
//#include"AddinManager1.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F2173DBD_A611_44D8_B708_3C8934D40CA1__INCLUDED_)
