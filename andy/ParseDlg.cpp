// ParseDlg.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "caddoc.h"
#include "ParseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParseDlg dialog


CParseDlg::CParseDlg()
{
	//{{AFX_DATA_INIT(CParseDlg)
//	m_com = _T("Command: ");
	m_log = _T("Welcome To AndyCad\r\n");
	//}}AFX_DATA_INIT
	com=_T("Command: ");
}


void CParseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParseDlg)
	DDX_Control(pDX, IDC_EDIT_COMMAND, m_com);
//	DDX_Text(pDX, IDC_EDIT_COMMAND, m_com);
	DDX_Text(pDX, IDC_EDIT_LOG, m_log);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParseDlg, CDialogBar)
	//{{AFX_MSG_MAP(CParseDlg)
	ON_EN_UPDATE(IDC_EDIT_COMMAND, OnUpdateEditCommand)
	ON_WM_CREATE()
	ON_MESSAGE(WM_INITDIALOG,OnInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParseDlg message handlers



int CParseDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	cur_i=0;
	cur_x=0;
	back=false;
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
		return 0;
}

void CParseDlg::setInterest(CSubject *sub)
{
	sub->RegisterInterest(this);
}

void CParseDlg::SendNotify(CString s, void *param[])
{
	if(s=="ViewInit")
	{
	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
		CView *pView = (CView *) pFrame->GetActiveView();
		parser=((CCadDoc*)pView->GetDocument())->m_parser;

		UpdateData(FALSE);
	}else
	if(s=="View")
	{
		CString i1=*(CString*)param[0];
		CString i2=*(CString*)param[1];

		parser->execute(i1,i2,this);
		update(i1,i2);
	}else
	if(s=="CancelCommand")
	{
			CString input,output;
			com="Command: ";
			input=com;
			output="Command Cancelled";
			parser->execute(input,output,this);
			update(input,output);
	}

}

void CParseDlg::OnUpdateEditCommand() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogBar::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
	UpdateData();
//	int i=m_com.GetLength()-1,j;
//	int i=0,j=0;
//	CEdit* pEditCom = (CEdit*) GetDlgItem (IDC_EDIT_COMMAND);
    
	CString input,input0;
//	pEditCom->GetSel(i,j);
	string c0;
	m_com.GetWindowText(input0);//GetSel(i,j);
	input0.TrimLeft();
	int i=input0.GetLength()-1,j;
	if(!back)
		cur_x++;
	else
		back=false;//=i+1;
	if(i>com.GetLength())
	{
		input= input0.Mid(com.GetLength());
	}

/*	else
	{
//		m_com.ReplaceSel(com);
		UpdateData(FALSE);
//		int i=m_com.GetLength();
//		pEditCom->SetSel(i,i);
	}*/
	i=input.GetLength();
	if((i>0)&&((input.Find('\n')==i-1)))//||(input.Find('\x20')==input.GetLength()-1)))
	{
		input.TrimRight();
		cmds.push_back(input);
		cur_i=cmds.size();
		CString output;
		parser->execute(input,output,this);
		update(input,output);
		com=input;
		cur_x=0;
	}
	
}

void CParseDlg::update(LPCTSTR input, LPCTSTR output)
{
		CString j,input0;
		if(output!="")
		{
		j.Format("%s",output);
		m_log+=j;
		}
		m_com.SetWindowText(input);
		int j0,i0;
		m_com.SetSel(0,-1);
		m_com.GetSel(i0,j0);
		m_com.SetSel(j0,j0);

//		com=input;
		CEdit* pEditLog = (CEdit*) GetDlgItem (IDC_EDIT_LOG);
		CEdit* pEditCom = (CEdit*) GetDlgItem (IDC_EDIT_COMMAND);
		int ip=pEditLog->GetLineCount(),op,mp;
		UpdateData(FALSE);
		op=pEditLog->GetLineCount();
		mp=pEditLog->GetFirstVisibleLine();
		
		ip=op-mp;
		pEditLog->LineScroll(ip);

		m_com.GetWindowText(input0);
//		pEditCom->SetSel(i,i);

}
bool CParseDlg::OnFromEditLButton(CPoint point) 
{
	int i=m_com.CharFromPos(point);
	int j=com.GetLength()-1;
	if(i>j)
	{
		cur_x=i-j;
		return true;
	}
	else
		return false;
}
bool CParseDlg::OnFromEditChar(UINT nChar) 
{
	// TODO: Add your message handler code here and/or call default
		CString input,input0;
		m_com.GetWindowText(input0);
		if(nChar==(UINT)(VK_ESCAPE))
		{
			CString input,output;
			com="Command: ";
			input=com;
			output="Command Cancelled";
			parser->execute(input,output,this);
			update(input,output);
		}
		if(nChar==(UINT)(VK_UP))
		{
			if(cur_i-1>=0)
			{
			cur_i--;
				int _size=cmds.size()-1;
				if(cur_i>_size)
				{
					cur_i--;
					return true;
				}
				input=cmds[cur_i];
//				CString f(cur_i);
//				(cur_i);
//				input+=f;
				input.TrimRight();
				cur_x=input.GetLength()-1;
				cur_x=cur_x<0?0:cur_x;
				update(com+input,"");
//				UpdateData(FALSE);
			}
		}else
		if(nChar==(UINT)(VK_DOWN))
		{
			if(cur_i+1<cmds.size())
			{
				cur_i++;
				int _size=cmds.size()-1;
				if(_size==0) return true;
				input=cmds[cur_i];
				input.TrimRight();
				cur_x=input.GetLength()-1;
				cur_x=cur_x<0?0:cur_x;
				update(com+input,"");
			}
		}else
		if(nChar==(UINT)(VK_DELETE))
		{
			if(cur_x<com.GetLength())
			{
				return false;
			}
		}else
		if(nChar==(UINT)(VK_LEFT))
		{

			if(cur_x<=0)//com.GetLength())
			{
				return false;
			}
			cur_x--;
		}else
		if(nChar==(UINT)(VK_BACK))
		{
			back=true;

			if(cur_x<=0)//com.GetLength())
			{
				return false;
			}
			cur_x--;
		}else
		if(nChar==(UINT)(VK_RIGHT))
		{
			input0= input0.Mid(com.GetLength());
			if(cur_x>=input0.GetLength())
			{
				return false;
			}
			cur_x++;
		}else
		if(nChar==(UINT)(VK_RETURN))
		{
			if(input0==com) return false;
			input0+="\n";
			m_com.SetWindowText(input0);

//			OnUpdateEditCommand();
//			return false;
		}
	return true;
}

LRESULT CParseDlg::OnInitDialog(WPARAM u,LPARAM v) 
{
	
	// TODO: Add extra initialization here
	CDialogBar::HandleInitDialog(u,v);
	CEditParse* pEditCom = (CEditParse*) GetDlgItem (IDC_EDIT_COMMAND);
	pEditCom->SetWindowText(_T("Command: "));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
