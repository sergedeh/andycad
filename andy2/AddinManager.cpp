
/* ----------------------------------- File Header -------------------------------------------*
	File				:	AddinManager.cpp
	Project Code		:	
	Author	    		:	Tom Thomas, 
	Created On	    	:	11/16/2004 12:00:47 PM
	Last Modified	   	:	12/1/2004 1:20:08 PM
----------------------------------------------------------------------------------------------*
	Type				:	C++ Source File
	Description			:   
	Developer's Note	:	Error Handling is not done prefectly. 
							Code is not production level. No code Optimization done.	
	Bugs				:	
	See Also			:	
	Revision History	:	
	Traceability        :	
	Necessary Files		:	
---------------------------------------------------------------------------------------------*/



#include "stdafx.h"
#include "ProjectFramework.h"
#include "AddinManager.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAddinManager::CAddinManager()
{
	m_bLoadAllAdins=TRUE;
}

CAddinManager::~CAddinManager()
{
	CoUninitialize();	
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::LoadAddinDefaultSettings
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::LoadAddinDefaultSettings
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
------------------------------------------------------------------------------------------------------------*/

BOOL CAddinManager::LoadAddinDefaultSettings()
{
	return TRUE;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::SaveAddinDefaultSettings
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
------------------------------------------------------------------------------------------------------------*/

BOOL CAddinManager::SaveAddinDefaultSettings()
{
	return TRUE;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::LoadAllAddins
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
------------------------------------------------------------------------------------------------------------*/

BOOL CAddinManager::LoadAllAddins()
{
	//Load all the addins here by looking 
	//at the default settings from the registry

	HRESULT m_hCoInitialize;
	HRESULT hResult = S_OK;          
	//COM Iniialize
	hResult = CoInitialize(NULL);
	if(SUCCEEDED(hResult))
	{
		m_hCoInitialize = hResult;
		hResult = m_ProjectFrameworkObject.CoCreateInstance(CLSID_ProjectFramework);
	}
	if(!SUCCEEDED(hResult))
	{
		AfxMessageBox("Project  Framework Object Failed");
		return FALSE;
	}
	AfxConnectionAdvise((LPUNKNOWN)m_ProjectFrameworkObject,
														  DIID__IProjectFrameworkEvents,
														  AfxGetApp()->GetIDispatch(FALSE),
														  FALSE,&m_dwCookie);

	CString strAddinSettingsInfo="";
	if(LoadAllAdins(strAddinSettingsInfo.AllocSysString(),m_ProjectFrameworkObject)==E_FAIL)
	{
		return FALSE;
	}

	return TRUE;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::GetAddinIffo
	Description	      : 
	Return Type	      : CAddinInfo 
	Warning           : 
  Argument          : CLSID clsID
------------------------------------------------------------------------------------------------------------*/

CAddinInfo CAddinManager::GetAddinIffo(CLSID clsID)
{
	CAddinInfo AddinInfo;
	//Iterate through the loop and 
	return AddinInfo;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::GetLoadAllAddinStatus
	Description	      : Override this function if you want to load all addin conditionally..
						That is depending upon the application settings.

	Return Type	      : BOOL 
	Warning           : 
------------------------------------------------------------------------------------------------------------*/

BOOL CAddinManager::GetLoadAllAddinStatus()
{
	return m_bLoadAllAdins;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::SetLoadAllAddinStatus
	Description	      : 
	Return Type	      : void 
	Warning           : 
  Argument          : BOOL bLoadAllAddins
------------------------------------------------------------------------------------------------------------*/

void CAddinManager::SetLoadAllAddinStatus(BOOL bLoadAllAddins)
{
	m_bLoadAllAdins=bLoadAllAddins;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::GetAddinCount
	Description	      : 
	Return Type	      : long 
	Warning           : 
------------------------------------------------------------------------------------------------------------*/

long CAddinManager::GetAddinCount()
{
	return m_AddinInfoArray.GetSize(); 
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::SetAddinInfo
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
  Argument          : long iAddinIndex
  Argument          : CAddinInfo AddinInfo
------------------------------------------------------------------------------------------------------------*/

BOOL CAddinManager::SetAddinInfo(long iAddinIndex,CAddinInfo AddinInfo)
{
	m_AddinInfoArray.SetAt(iAddinIndex,AddinInfo); 
	return TRUE;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::GetAddinInfo
	Description	      : 
	Return Type	      : CAddinInfo 
	Warning           : 
  Argument          : long iAddinIndex
------------------------------------------------------------------------------------------------------------*/

CAddinInfo CAddinManager::GetAddinInfo(long iAddinIndex)
{
	
	//Iterate through the loop and 
	return m_AddinInfoArray[iAddinIndex];
}

BOOL CAddinManager::UnloadAllAddins()
{

	AfxConnectionUnadvise((LPUNKNOWN)m_ProjectFrameworkObject,
														  DIID__IProjectFrameworkEvents,
														  AfxGetApp()->GetIDispatch(FALSE),
														  FALSE,m_dwCookie);
	m_ProjectFrameworkObject.Release();
	for(int i=0;i<m_AddinInfoArray.GetSize();i++)
	{
		m_AddinInfoArray[i].m_pProjectFrameworkAddin->Release();  
	}
	CoUninitialize();
	return TRUE;
}

BOOL CAddinManager::SetAddinCount(long lCount)
{
	m_AddinInfoArray.SetSize(lCount);
	return TRUE;
}

BOOL CAddinManager::AddAddinCommandInfo(long iAddinIndex, CAddinCommadInfo AddinCommadInfo)
{
	m_AddinInfoArray[iAddinIndex].m_AddinCommadInfoArray.Add(AddinCommadInfo);
	return TRUE;
}

CAddinCommadInfo CAddinManager::GetAddinCommadInfo(long iAddinIndex,long lIndex)
{
	return m_AddinInfoArray[iAddinIndex].m_AddinCommadInfoArray[lIndex];
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::GetAddinCommadInfo
	Description	      : 
	Return Type	      : const CAddinCommadInfo& 
	Warning           : 
  Argument          : UINT iCommandID
------------------------------------------------------------------------------------------------------------*/

const CAddinCommadInfo& CAddinManager::GetAddinCommadInfo(UINT iCommandID)
{
	static CAddinCommadInfo AddinCommadInfo;
	AddinCommadInfo.m_iCommandID=0; 
	for(int i=0;i<m_AddinInfoArray.GetSize();i++)
	{
		for(int j=0;j<m_AddinInfoArray[i].m_AddinCommadInfoArray.GetSize();j++)
		{
			if(m_AddinInfoArray[i].m_AddinCommadInfoArray[j].m_iCommandID==iCommandID)
			{
				return m_AddinInfoArray[i].m_AddinCommadInfoArray[j];
			}
		}
	}
	return AddinCommadInfo;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::GetAddinInformation
	Description	      : 
	Return Type	      : const CAddinInfo& 
	Warning           : 
  Argument          : UINT iCommandID
------------------------------------------------------------------------------------------------------------*/

const CAddinInfo& CAddinManager::GetAddinInformation(UINT iCommandID)
{
	static CAddinInfo AddinInfo;
	for(int i=0;i<m_AddinInfoArray.GetSize();i++)
	{
		for(int j=0;j<m_AddinInfoArray[i].m_AddinCommadInfoArray.GetSize();j++)
		{
			if(m_AddinInfoArray[i].m_AddinCommadInfoArray[j].m_iCommandID==iCommandID)
			{
				return m_AddinInfoArray[i];
			}
		}
	}
	return AddinInfo;
}

BOOL CAddinManager::SetAddinVisible(CString strAddinName, BOOL bVisible)
{
	for(int i=0;i<m_AddinInfoArray.GetSize();i++)
	{
		if(m_AddinInfoArray[i].m_strAddinName==strAddinName)
		{
			m_AddinInfoArray[i].m_bLoadAddin=bVisible;
			return TRUE;
		}
	}
	return FALSE;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::InvokeAddinMenuItem
	Description	      : Ivokes function corresponding to addin menu item
	Return Type	      : BOOL 
	Warning           : 
  Argument          : UINT nID
------------------------------------------------------------------------------------------------------------*/

BOOL CAddinManager::InvokeAddinMenuItem(UINT nID)
{
	try
	{
		const CAddinInfo& AddinInfo=GetAddinInformation(nID);
		const CAddinCommadInfo& AddinCommadInfo=GetAddinCommadInfo(nID);
		HRESULT hResult=E_FAIL;
		IDispatch * pDisp = (IDispatch *)NULL;
		DISPID dispid;
		CString strFunction=AddinCommadInfo.m_strFunction;
		//OLECHAR FAR* szMember = (OLECHAR FAR*)strFunction.GetBuffer(strFunction.GetLength());

		OLECHAR FAR* szMember = strFunction.AllocSysString() ;

		// Code that sets a pointer to the dispatch (pdisp) is omitted.
		
		DISPPARAMS  DispParams;
		memset(&DispParams, 0, sizeof DispParams);
		VARIANT VarResult;
		memset(&VarResult, 0, sizeof VarResult);
		EXCEPINFO ExcepInfo;
		memset(&ExcepInfo, 0, sizeof ExcepInfo);
		unsigned int uArgErr=0;
		
		hResult = AddinInfo.m_pProjectFrameworkAddin->QueryInterface(IID_IDispatch,(void **)&pDisp);
		if(SUCCEEDED(hResult))
		{
			hResult=pDisp->GetIDsOfNames(IID_NULL,&szMember, 1, LOCALE_SYSTEM_DEFAULT,&dispid);
			if(FAILED(hResult))
			{
				return FALSE;
			}
			//Get the DispId so call the invoke function after filling the parameters
			hResult=pDisp->Invoke(dispid,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_METHOD|DISPATCH_PROPERTYGET ,&DispParams,&VarResult,&ExcepInfo,&uArgErr); 
			if(FAILED(hResult))
			{
				CString strErrorString;
				strErrorString.Format("Faild to invoke %s function",strFunction);
				AfxMessageBox(strErrorString);
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CAddinManager::LoadAllAdins
	Description	      : Loads all the addins belonging the certain catogory ID CATID_PROJECT_FRAMEWORK_ADDINS
	Return Type	      : HRESULT 
	Warning           : 
  Argument          : BSTR strAddinLoadingInfo , settings information from file/registry about which addin to load etc
  Argument          : IProjectFramework* pProjectFramework
------------------------------------------------------------------------------------------------------------*/

HRESULT CAddinManager::LoadAllAdins(BSTR strAddinLoadingInfo,IProjectFramework* pProjectFramework)
{
	try
	{
		CString strAddinLoadingInformation=strAddinLoadingInfo;
		if(strAddinLoadingInformation=="")
		{
			//Load All addins
			CATID catid = CATID_PROJECT_FRAMEWORK_ADDINS;
			CLSID clsid[40];
			ICatInformation *pCatInfo = NULL;
			HRESULT hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 0,
						CLSCTX_SERVER, IID_ICatInformation, (void **)&pCatInfo);
			if (!SUCCEEDED(hr))
			{
				AfxMessageBox("Catagory Failed");
				return E_FAIL;
			}
			IEnumCLSID *pCLSID = NULL;
			CATID catids[1];
			catids[0] = catid;
			int iAddinCount=0;
			hr = pCatInfo->EnumClassesOfCategories(1, catids, -1, 0, &pCLSID);
			do
			{
				DWORD num = 0;
				hr = pCLSID->Next(40, clsid, &num);
				if(!SUCCEEDED(hr))
				{
					AfxMessageBox("Class ID  Failed");
					return E_FAIL;
				}
				iAddinCount=iAddinCount+num;
				CProjectFrameworkApp::m_AddinManager.SetAddinCount(iAddinCount); 
				for (long i = 0; i < (long)num; i++)
				{
					IProjectFrameworkAddin *pProjectFrameworkAddin = NULL;
					
					hr = CoCreateInstance(clsid[i], NULL,CLSCTX_INPROC_SERVER,IID_IProjectFrameworkAddin, (void **)&pProjectFrameworkAddin);
					
					if(SUCCEEDED(hr))
					{
						CAddinInfo AddinInfo;
						AddinInfo.m_pProjectFrameworkAddin=pProjectFrameworkAddin;
						AddinInfo.m_clsID=clsid[i];
						CProjectFrameworkApp::m_AddinManager.SetAddinInfo(i,AddinInfo);
						VARIANT bFirstTime;
						bFirstTime.vt =VT_BOOL;
						bFirstTime.boolVal=TRUE; 
						pProjectFrameworkAddin->Initialize(i, pProjectFramework,bFirstTime);
					}
					else
					{
																				
					}
				
				}
				
			} while (hr == S_OK);
			pCLSID->Release();
			pCatInfo->Release();
			//Fill the session manager with the routing table
			return S_OK;
		}
		else
		{
			//Load selected addins
		}
	}
	
	catch(...)
	{
		AfxMessageBox("Generic Error");
		return E_FAIL;
	}

	return S_OK;
}
