// MacroManager.cpp: implementation of the CMacroManager class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "MacroManager.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMacroManager::CMacroManager()
{

}

CMacroManager::~CMacroManager()
{

}


HRESULT CMacroManager::SetAddInInfo(long lSessionID,BSTR strXMLMenuToolbarIDCmdInfo, long lToobarRes)
{
	CAddinInfo AddinInfo=CCadApp::m_AddinManager.GetAddinInfo(lSessionID);
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

BOOL CMacroManager::GetAllCommandsInfo(CAddinInfo &AddinInfo, IXMLDOMNodeList *pXMLDOMNodeList)
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


BOOL CMacroManager::ParseAndLoadCommandInfo(BSTR strXMLCommand, CAddinInfo &AddinInfo)
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


HRESULT CMacroManager::LoadAllMacros(int &i)
{

	// Find all files in the current directory with the
	// macro file extension, ".mac".
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if ( strPath[strPath.GetLength()-1] != '\\' ) {
		// The directory doesn't end with a backslash,
		// so we add one now.
		strPath += '\\';
	} // if
	CString strFile = strPath + "*.xml";
	WIN32_FIND_DATA wfd;
	HANDLE hSearchHandle = FindFirstFile(strFile,&wfd);
	if ( hSearchHandle != INVALID_HANDLE_VALUE ) {
		// Pull first filename
		CString strXMLCommandSub,strXMLCommandSub2,s;
		TRY
		{

		CStdioFile f(wfd.cFileName,CFile::modeRead);
		while(f.ReadString(s))
			strXMLCommandSub+=s;
		}
		CATCH( CFileException, e )
		{
  		 ::AfxMessageBox("File not found",IDOK);

		}
		END_CATCH
		CCadApp::m_AddinManager.SetAddinCount(i+1);
		SetAddInInfo(i,strXMLCommandSub.AllocSysString(),NULL);i++;
		while ( FindNextFile(hSearchHandle,&wfd) ) {
			// While we have more files...
			TRY
			{
			CStdioFile f(wfd.cFileName,CFile::modeRead);
			while(f.ReadString(s))
				strXMLCommandSub+=s;
			}
			CATCH( CFileException, e )
			{
  			 ::AfxMessageBox("File not found",IDOK);

			}
			END_CATCH
			CCadApp::m_AddinManager.SetAddinCount(i+1);
			SetAddInInfo(i,strXMLCommandSub.AllocSysString(),NULL);i++;

		} // while

		// Close our search handle
		FindClose(hSearchHandle);
	} // if
	
	return S_OK;

}

void CMacroManager::LoadandRunScript(CString strPath)
{
	CString strMac,strXMLCommandSub2,s;
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	CString strFile = strPath + "*.vbs";
	WIN32_FIND_DATA wfd;
	HANDLE hSearchHandle = FindFirstFile(strFile,&wfd);
	SetCurrentDirectory(strPath);
	if ( hSearchHandle != INVALID_HANDLE_VALUE ) {
		
		TRY
		{
		CStdioFile f(wfd.cFileName,CFile::modeRead);
		while(f.ReadString(s))
		{
			strMac+=s;
			strMac+='\n';
		}

		}
		CATCH( CFileException, e )
		{
		   #ifdef _DEBUG
			  afxDump << "File could not be opened "
					  << e->m_cause << "\n";
		   #endif
		}
		END_CATCH

		
		// Pull first filename
			if(strMac.GetLength()!=NULL) mg->RunMacro(strMac);
			strMac.Empty();
		while ( FindNextFile(hSearchHandle,&wfd) ) {
			// While we have more files...
		CStdioFile f(wfd.cFileName,CFile::modeRead);
		while(f.ReadString(s))
		{
			strMac+=s;
			strMac+='\n';
		}
			if(strMac.GetLength()!=NULL) mg->RunMacro(strMac);
			strMac.Empty();
		}
	}
	
	// Close our search handle
	FindClose(hSearchHandle);
} 
