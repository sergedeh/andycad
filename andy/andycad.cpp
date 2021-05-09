// AndyCad.cpp : Implementation of CAndyCad
#include "stdafx.h"
#include "Cad.h"
#include "CadAddIn.h"
#include "AndyCad.h"

/////////////////////////////////////////////////////////////////////////////
// CAndyCad

STDMETHODIMP CAndyCad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAndyCad
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAndyCad::get_MainWindow(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	HWND hMainWnd=AfxGetApp()->m_pMainWnd->m_hWnd;	
	*pVal=(long)hMainWnd; 
	return S_OK;
}

STDMETHODIMP CAndyCad::SendStatus(BSTR strStatus)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Fire_NotifyStatus(strStatus);

	return S_OK;
}
/*
STDMETHODIMP CAndyCad::SetAddInInfo(long lSessionID, long lInstanceHandle, BSTR strXMLMenuToolbarIDCmdInfo, long lToobarRes)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CAddinInfo AddinInfo=CCadApp::m_AddinManager.GetAddinInfo(lSessionID);
	AddinInfo.m_lInstanceHandle=lInstanceHandle;
	AddinInfo.m_lToobarRes=lToobarRes;
	
	CString strXMLCommand;
	strXMLCommand=strXMLMenuToolbarIDCmdInfo;
	if(ParseAndLoadCommandInfo(strXMLMenuToolbarIDCmdInfo,AddinInfo))
	{
		CCadApp::m_AddinManager.SetAddinInfo(lSessionID,AddinInfo); 
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}
*/
/*STDMETHODIMP CAndyCad::SetAddinToolbar(long lAddinIndex, VARIANT varValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}
*/
STDMETHODIMP CAndyCad::SetViewHeading(BSTR strHeading1, BSTR strHeading2, BSTR strHeading3)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CProjectFramework::GetAllCommandsInfo
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
  Argument          : CAddinInfo &AddinInfo
  Argument          : IXMLDOMNodeList *pXMLDOMNodeList
------------------------------------------------------------------------------------------------------------*/
/*
BOOL CAndyCad::GetAllCommandsInfo(CAddinInfo &AddinInfo, IXMLDOMNodeList *pXMLDOMNodeList)
{
	IXMLDOMNode			*pXMLDOMNode = NULL,*pXMLDOMLeafNode=NULL,*pXMLParentNode=NULL;
	IXMLDOMNodeList		*pXMLDOMChileNodeList = NULL;
	HRESULT hr =S_OK;
	hr=pXMLDOMNodeList->nextNode(&pXMLDOMNode);
	while(pXMLDOMNode!=NULL)
	{
		//Get all the node values and add it to CAddinCommadInfo class
		CAddinCommadInfo AddinCommadInfo;
		CString strMenuName;
		VARIANT varValue;
		hr=pXMLDOMNode->get_childNodes(&pXMLDOMChileNodeList);

		pXMLDOMChileNodeList->nextNode(&pXMLDOMLeafNode);
		while(pXMLDOMLeafNode!=NULL)
		{
			
			CString strNodeName="";
			BSTR strNodeTypeString;
			pXMLDOMLeafNode->get_nodeName(&strNodeTypeString);
			strNodeName=strNodeTypeString;
			pXMLDOMLeafNode->get_nodeTypedValue(&varValue);
			CString strValue=varValue.bstrVal;
			if(strNodeName=="Name")
			{
				AddinCommadInfo.m_strMenuString=strValue; 
			}
			else if(strNodeName=="FunctionName")
			{
				AddinCommadInfo.m_strFunction=strValue; 
			}
			else if(strNodeName=="HelpString")
			{
				AddinCommadInfo.m_strHelpString=strValue; 
			}
			else if(strNodeName=="ToolTip")
			{
				AddinCommadInfo.m_strToolTip=strValue; 
			}
			else if(strNodeName=="ToolBarIndex")
			{
				AddinCommadInfo.m_iToolbarIndex=atoi(strValue); 
			}
			else if(strNodeName=="ShortCutKey")
			{
				AddinCommadInfo.m_strShortCutKey=strValue; 
			}
			
			else if(strNodeName=="Separator")
			{
				AddinCommadInfo.m_iSeparator=atoi(strValue); 
			}
			else if(strNodeName=="ShortcutKeyIndex")
			{
				int index=atoi(strValue);
				if(AddinCommadInfo.m_strMenuString.GetLength() >=index)
				{
					AddinCommadInfo.m_strMenuString.Insert(index,"&"); 
				}
				
			}

			pXMLDOMChileNodeList->nextNode(&pXMLDOMLeafNode);
		}
		//Get all parent menus
		hr=pXMLDOMNode->get_parentNode(&pXMLParentNode);
		while(pXMLParentNode!=NULL)
		{
			BSTR strNodeTypeString;
			pXMLParentNode->get_nodeName(&strNodeTypeString);
			CString strNodeName=strNodeTypeString;
			//Get the child nodes
			hr=pXMLParentNode->get_childNodes(&pXMLDOMChileNodeList);

			pXMLDOMChileNodeList->nextNode(&pXMLDOMLeafNode);
			while(pXMLDOMLeafNode!=NULL)
			{
				BSTR strNodeTypeString;
				pXMLDOMLeafNode->get_nodeName(&strNodeTypeString);
				CString strNodeMenuName=strNodeTypeString;
				pXMLDOMLeafNode->get_nodeTypedValue(&varValue);
				CString strValue=varValue.bstrVal;
				if(strNodeMenuName=="Name")
				{
					AddinCommadInfo.m_MenuStringsArray.Add(strValue);
					
				}
				else if(strNodeMenuName=="ShortcutKeyIndex")
				{
					int index=atoi(strValue);
					if(AddinCommadInfo.m_MenuStringsArray[AddinCommadInfo.m_MenuStringsArray.GetSize()-1].GetLength()>=index)
					{
						AddinCommadInfo.m_MenuStringsArray[AddinCommadInfo.m_MenuStringsArray.GetSize()-1].Insert(index,"&");
					}
					break;					
				}
				pXMLDOMChileNodeList->nextNode(&pXMLDOMLeafNode);
			}

			if(strNodeName=="MainMenu")
			{
				break;
			}
			
			pXMLParentNode->get_parentNode(&pXMLParentNode);		
		}
		//Reverse the menu;
		CStringArray MenuArrayReversed;
		//Copy it to another array
		MenuArrayReversed.Copy(AddinCommadInfo.m_MenuStringsArray);
		//Remove it fdrom the existing array
		AddinCommadInfo.m_MenuStringsArray.RemoveAll();
		for(int i=MenuArrayReversed.GetSize()-1;i>=0;i--)
		{
			//Add it again
			AddinCommadInfo.m_MenuStringsArray.Add(MenuArrayReversed[i]);
		}
		//Now add the whole to the command list		
		AddinInfo.m_AddinCommadInfoArray.Add(AddinCommadInfo); 
		
			
		hr=pXMLDOMNodeList->nextNode(&pXMLDOMNode);
	}
	return TRUE;
}

BOOL CAndyCad::ParseAndLoadCommandInfo(BSTR strXMLCommand, CAddinInfo &AddinInfo)
{
	try
	{
		USES_CONVERSION;

		CComPtr<IXMLDOMDocument> spXMLDOM;
		IXMLDOMNodeList		*pXMLDOMNodeList = NULL;
		IXMLDOMNode			*pXMLDOMNode = NULL;
		int iAppVer=0;
		HRESULT hr = spXMLDOM.CoCreateInstance(	__uuidof(DOMDocument));
		if ( FAILED(hr) )
		{
			AfxMessageBox("Unable to create XML parser object");
			return FALSE;
		}
		if ( spXMLDOM.p == NULL ) 
		{
			AfxMessageBox("Unable to create XML parser object");
			return FALSE;
		}
		VARIANT_BOOL bSuccess = false;
		hr=spXMLDOM->loadXML(strXMLCommand,&bSuccess);
		if ( FAILED(hr) )
		{
			AfxMessageBox("Unable to load XML document into the parser");
			return FALSE;
		}
		if (!bSuccess )
		{
			AfxMessageBox("Unable to load XML document into the parser");
			return FALSE;
		}
		//Get The application Name
		hr=spXMLDOM->getElementsByTagName(CComBSTR("AddinName"),&pXMLDOMNodeList);
		if ( FAILED(hr) )
		{
			AfxMessageBox("Failed to get the Addin Name");
			return FALSE;
		}
		else
		{
			hr=pXMLDOMNodeList->nextNode(&pXMLDOMNode);
			VARIANT varValue;
			pXMLDOMNode->get_nodeTypedValue(&varValue);
			AddinInfo.m_strAddinName=varValue.bstrVal; //Got the addin Name
			
		}
		
		//Get The Toolbar button count
		hr=spXMLDOM->getElementsByTagName(CComBSTR("ToobarButtonCount"),&pXMLDOMNodeList);
		if ( FAILED(hr) )
		{
			AfxMessageBox("Failed to get the Toolbar button count");
			return FALSE;
		}
		else
		{
			hr=pXMLDOMNodeList->nextNode(&pXMLDOMNode);
			VARIANT varValue;
			pXMLDOMNode->get_nodeTypedValue(&varValue);
			AddinInfo.m_lToolbarButtonCount =atoi(W2A(varValue.bstrVal)); //Got the toolbar button count
			
		}

		//Get the App Version
		hr=spXMLDOM->getElementsByTagName(CComBSTR("AppVer"),&pXMLDOMNodeList);
		if ( FAILED(hr) )
		{
			AfxMessageBox("Failed to get the Appllication Version");
			return FALSE;
		}
		else
		{
			hr=pXMLDOMNodeList->nextNode(&pXMLDOMNode);
			VARIANT varValue;
			pXMLDOMNode->get_nodeTypedValue(&varValue);
			iAppVer=atoi(W2A(varValue.bstrVal));
			
		}
		switch(iAppVer) //Check for the application Version
		{
			case 2:
				//Get all the leaf menu nodes
				hr=spXMLDOM->getElementsByTagName(CComBSTR("LeafMenu"),&pXMLDOMNodeList);
				if ( FAILED(hr) )
				{
					AfxMessageBox("Failed to get Commands information");
					return FALSE;
				}
				else
				{
					if(!GetAllCommandsInfo(AddinInfo,pXMLDOMNodeList))
					{
						AfxMessageBox("Failed to get all commands information");
						return FALSE;
					}
				}
				break;
			default:
				AfxMessageBox("Unknown Version Format..");
				return FALSE;
				break;
		}
	

	}
	catch(_com_error ex)
	{
		AfxMessageBox(ex.ErrorMessage());
		return FALSE;
	}
	catch(...)
	{
		AfxMessageBox("Generic Error");
		return FALSE;
	}
	return TRUE;
}

STDMETHODIMP CAndyCad::LoadAllAdins(BSTR strAddinLoadingInfo)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;

}
*/