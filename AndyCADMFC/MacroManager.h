// MacroManager.h: interface for the CMacroManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACROMANAGER_H__B61093CE_31AE_46ED_9511_A4E3C39F89FB__INCLUDED_)
#define AFX_MACROMANAGER_H__B61093CE_31AE_46ED_9511_A4E3C39F89FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#import "msxml.dll" named_guids raw_interfaces_only
using namespace MSXML;


class CMacroManager  
{
public:
	void LoadandRunScript(CString strPath);
	HRESULT LoadAllMacros(int &i);
	CMacroManager();
	virtual ~CMacroManager();
	BOOL GetAllCommandsInfo(CAddinInfo& AddinInfo, IXMLDOMNodeList* pXMLDOMNodeList);
	BOOL ParseAndLoadCommandInfo(BSTR strXMLCommand, CAddinInfo& AddinInfo);
	HRESULT SetAddInInfo (long lSessionID, BSTR strXMLMenuToolbarIDCmdInfo, long lToobarRes);

};

#endif // !defined(AFX_MACROMANAGER_H__B61093CE_31AE_46ED_9511_A4E3C39F89FB__INCLUDED_)
