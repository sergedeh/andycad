
/* ----------------------------------- File Header -------------------------------------------*
	File				:	AddinManager.h
	Project Code		:	
	Author	    		:	Tom Thomas
	Created On	    	:	11/16/2004 12:00:47 PM
	Last Modified	   	:	11/16/2004 12:00:47 PM
----------------------------------------------------------------------------------------------*
	Type				:	Header File
	Description			:   
	Developer's Note	:	
	Bugs				:	
	See Also			:	
	Revision History	:	
	Traceability        :	
	Necessary Files		:	
---------------------------------------------------------------------------------------------*/

// AddinManager.h: interface for the CAddinManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADDINMANAGER_H__05912DF7_1D86_4BC0_8FFF_3C96FB95B749__INCLUDED_)
#define AFX_ADDINMANAGER_H__05912DF7_1D86_4BC0_8FFF_3C96FB95B749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "projectframework_i.h"

#define PF_ADDIN_CMD_MIN_MSG_ID				WM_USER+1000

#define PF_ADDIN_CMD_MAX_MSG_ID				WM_USER+10000
			
/*----------------------------------- Class Header ------------------------------------------*
	Name				:	CAddinCommadInfo
	Date of Creation	:	10/1/2004 5:41:37 PM
	Type				:	BASE
	Functionality		:   
---------------------------------------------------------------------------------------------*/
class CAddinCommadInfo
{
public:
	CStringArray m_MenuStringsArray; //All Menus before coming to the leaf node
	UINT m_iCommandID;
	CString m_strMenuString;
	CString m_strHelpString;
	CString m_strToolTip;
	CString m_strFunction;
	CString m_strShortCutKey;
	int m_iToolbarIndex;
	UINT m_iSeparator;
	CArray<VARIANT,VARIANT> m_VarArgs;
	CAddinCommadInfo()
	{	
		m_iCommandID=0;
		m_iSeparator=0;
		m_iToolbarIndex=-1;
	}
	CAddinCommadInfo(CAddinCommadInfo& AddinCommadInfo)
	{
		m_iCommandID=AddinCommadInfo.m_iCommandID;
		m_strFunction=AddinCommadInfo.m_strFunction;
		m_strMenuString=AddinCommadInfo.m_strMenuString;
		m_strHelpString=AddinCommadInfo.m_strHelpString;
		m_strToolTip=AddinCommadInfo.m_strToolTip;
		m_strShortCutKey=AddinCommadInfo.m_strShortCutKey;
		m_iToolbarIndex=AddinCommadInfo.m_iToolbarIndex;
		m_iSeparator=AddinCommadInfo.m_iSeparator;

		m_VarArgs.Copy(AddinCommadInfo.m_VarArgs);
		m_MenuStringsArray.Copy(AddinCommadInfo.m_MenuStringsArray);

	}
	operator =(CAddinCommadInfo& AddinCommadInfo)
	{
		m_iCommandID=AddinCommadInfo.m_iCommandID;
		m_strFunction=AddinCommadInfo.m_strFunction;
		m_strMenuString=AddinCommadInfo.m_strMenuString;
		m_strHelpString=AddinCommadInfo.m_strHelpString;
		m_strToolTip=AddinCommadInfo.m_strToolTip;
		m_strShortCutKey=AddinCommadInfo.m_strShortCutKey;
		m_iToolbarIndex=AddinCommadInfo.m_iToolbarIndex;
		m_iSeparator=AddinCommadInfo.m_iSeparator;

		m_VarArgs.Copy(AddinCommadInfo.m_VarArgs);
		m_MenuStringsArray.Copy(AddinCommadInfo.m_MenuStringsArray);
	}
	
};

/*----------------------------------- Class Header ------------------------------------------*
	Name				:	CAddinInfo
	Date of Creation	:	10/1/2004 1:20:53 PM
	Type				:	BASE
	Functionality		:   
---------------------------------------------------------------------------------------------*/

class CAddinInfo
{
public:
	CLSID m_clsID;
	CString m_strAddinName;
	long m_lInstanceHandle;
	long m_lToobarRes;
	BOOL m_bLoadAddin;
	UINT m_lToolbarButtonCount;
	IProjectFrameworkAddin* m_pProjectFrameworkAddin;
	CArray<CAddinCommadInfo,CAddinCommadInfo> m_AddinCommadInfoArray;
	CAddinInfo()
	{
		m_pProjectFrameworkAddin=NULL;
		m_strAddinName="";
		m_bLoadAddin=TRUE;
		m_lToolbarButtonCount=0;
	}
	CAddinInfo(CAddinInfo& AddinInfo)
	{
		m_clsID=AddinInfo.m_clsID;
		m_lInstanceHandle=AddinInfo.m_lInstanceHandle;
		m_lToobarRes=AddinInfo.m_lToobarRes;
		m_pProjectFrameworkAddin=AddinInfo.m_pProjectFrameworkAddin ;
		m_strAddinName=AddinInfo.m_strAddinName;
		m_bLoadAddin=AddinInfo.m_bLoadAddin;
		m_lToolbarButtonCount=AddinInfo.m_lToolbarButtonCount;
		
		m_AddinCommadInfoArray.SetSize(AddinInfo.m_AddinCommadInfoArray.GetSize());
		for(int i=0;i<m_AddinCommadInfoArray.GetSize();i++)
		{
			m_AddinCommadInfoArray[i]=AddinInfo.m_AddinCommadInfoArray[i];
		}
		
	}
	operator =(CAddinInfo& AddinInfo)
	{
		m_clsID=AddinInfo.m_clsID;
		m_lInstanceHandle=AddinInfo.m_lInstanceHandle;
		m_lToobarRes=AddinInfo.m_lToobarRes;
		m_pProjectFrameworkAddin=AddinInfo.m_pProjectFrameworkAddin ;
		m_strAddinName=AddinInfo.m_strAddinName;
		m_bLoadAddin=AddinInfo.m_bLoadAddin;
		m_lToolbarButtonCount=AddinInfo.m_lToolbarButtonCount;
		m_AddinCommadInfoArray.SetSize(AddinInfo.m_AddinCommadInfoArray.GetSize());
		for(int i=0;i<m_AddinCommadInfoArray.GetSize();i++)
		{
			m_AddinCommadInfoArray[i]=AddinInfo.m_AddinCommadInfoArray[i];
		}
	}
	
};


/*----------------------------------- Class Header ------------------------------------------*
	Name				:	CAddinManager
	Date of Creation	:	10/1/2004 1:20:47 PM
	Type				:	BASE
	Functionality		:   
---------------------------------------------------------------------------------------------*/

class CAddinManager  
{
private:
	DWORD m_dwCookie;
	BOOL m_bLoadAllAdins;
	CArray<CAddinInfo,CAddinInfo> m_AddinInfoArray;
	CComPtr<IProjectFramework> m_ProjectFrameworkObject;
	HRESULT LoadAllAdins(BSTR strAddinLoadingInfo,IProjectFramework* pProjectFramework);
public:
	
	BOOL InvokeAddinMenuItem(UINT iCommandID);
	BOOL SetAddinVisible(CString strAddinName, BOOL bVisible);
	const CAddinInfo& GetAddinInformation(UINT iCommandID);
	const CAddinCommadInfo& GetAddinCommadInfo(UINT iCommandID);
	CAddinCommadInfo GetAddinCommadInfo(long iAddinIndex,long lIndex);
	BOOL AddAddinCommandInfo(long iAddinIndex, CAddinCommadInfo AddinCommadInfo);
	BOOL SetAddinCount(long lCount);
	BOOL UnloadAllAddins();
	CAddinInfo GetAddinInfo(long iAddinIndex);
	BOOL SetAddinInfo(long iAddinIndex,CAddinInfo AddinInfo);
	long GetAddinCount();
	void SetLoadAllAddinStatus(BOOL bLoadAllAddins);
	virtual BOOL GetLoadAllAddinStatus();
	CAddinInfo GetAddinIffo(CLSID clsID);
	
	
	BOOL LoadAllAddins();
	BOOL SaveAddinDefaultSettings();
	BOOL LoadAddinDefaultSettings();
	
	CAddinManager();
	virtual ~CAddinManager();

};

#endif // !defined(AFX_ADDINMANAGER_H__05912DF7_1D86_4BC0_8FFF_3C96FB95B749__INCLUDED_)
