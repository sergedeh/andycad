// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
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


#define WIDTHBYTES(bits) ((((bits)+31)/32)*4)

#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
#include <Afxctl.h>





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

#endif //PCH_H
