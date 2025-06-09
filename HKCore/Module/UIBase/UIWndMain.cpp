//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndMain.cpp  CUIWndMain


#include "stdafx.h"
#include "UIWndMain.h"
#include "UIWndThread.h"

CString CUIWndMain::g_strMainPageFile = _T("Main.xml");

CUIWndMain::CUIWndMain()
{
	//初始化属性
	m_nUseFrame = 0;

	//初始化成员变量
	m_pActivePage = NULL;
	m_pPagesDef = NULL;
}

CUIWndMain::~CUIWndMain()
{
	Destroy();
	m_oUIHistoryPage.RemoveAll();
}

BOOL CUIWndMain::Destroy()
{
	DeleteAll();
	return TRUE;
}

long CUIWndMain::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowList::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strStartPageKey, oNode, m_strStartPage);
	xml_GetAttibuteValue(pXmlKeys->m_strUseFrameKey, oNode, m_nUseFrame);
	return 0;
}

long CUIWndMain::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStartPageKey, oElement, m_strStartPage);
	xml_SetAttributeValue(pXmlKeys->m_strUseFrameKey, oElement, m_nUseFrame);
	return 0;
}

long CUIWndMain::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowList::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strStartPage);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseFrame);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strStartPage);
		BinarySerializeRead(oBinaryBuffer, m_nUseFrame);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strStartPage);
		BinarySerializeWrite(oBinaryBuffer, m_nUseFrame);
	}
	return 0;
}

void CUIWndMain::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == UICLASSID_CUIWNDPAGESDEF)
		{
			m_pPagesDef = (CUIWndPagesDef*)p;
		}
	}

	CUIWindowList::InitAfterRead();
}

BOOL CUIWndMain::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowList::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndMain *p = (CUIWndMain*)pObj;

	if(m_strStartPage != p->m_strStartPage)
	{
		return FALSE;
	}

	if(m_nUseFrame != p->m_nUseFrame)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndMain::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowList::CopyOwn(pDest);

	CUIWndMain *p = (CUIWndMain*)pDest;

	p->m_strStartPage = m_strStartPage;
	p->m_nUseFrame = m_nUseFrame;
	return TRUE;
}

CBaseObject* CUIWndMain::Clone()
{
	CUIWndMain *p = new CUIWndMain();
	Copy(p);
	return p;
}

BOOL CUIWndMain::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIWNDPAGESDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIWndMain::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIWndPagesDefKey)
	{
		pNew = new CUIWndPagesDef();
	}

	return pNew;
}

CExBaseObject* CUIWndMain::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIWNDPAGESDEF)
	{
		pNew = new CUIWndPagesDef();
	}

	return pNew;
}

void CUIWndMain::Load(const CString &strMainPageFile)
{
	CString strFile;
	strFile = _P_GetResourcePath();

	if (strMainPageFile.GetLength() >= 5)
	{
		strFile += strMainPageFile;
	}
	else
	{
		strFile += g_strMainPageFile;
	}

	OpenXmlFile(strFile, CUIBaseXmlRWKeys::CUIWndMainKey(), CUIBaseXmlRWKeys::g_pXmlKeys);

	ShowPage(m_strStartPage, 1);//显示起始页面

	if (m_pActivePage == NULL)
	{
		AfxMessageBox(_T("没有定义起始页"));
		AfxGetMainWnd()->PostMessage(WM_EXITINSTANCE, 0, 0);
		return;
	}

	if (m_pActivePage->m_pWindow != NULL)
	{
		m_pActivePage->m_pWindow->BringWindowToTop();
		m_pActivePage->m_pWindow->SetFocus();
	}

	mouse_event(MOUSEEVENTF_MOVE, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

}

//////////////////////////////////////////////////////////////////////////

BOOL CUIWndMain::ClosePage(const CString &strPage)
{	
	if (strPage.GetLength() == 0)
	{
		ClosePage();
	}
	else
	{
		CUIWndPage *pPage = (CUIWndPage*)FindByID(strPage);
		ClosePage(pPage);
	}

	return TRUE;
}

BOOL CUIWndMain::ClosePage()
{
	CUIWndPage *pPage = (CUIWndPage*)m_oUIHistoryPage.GetTail();

	if (pPage != m_pActivePage || pPage == NULL) 
	{
		return FALSE;
	}

	ClosePage(pPage);	

	return TRUE;
}


BOOL CUIWndMain::ClosePage(CUIWndPage *pPage, BOOL bPostExitMsg)
{
	if (pPage != NULL)
	{
		pPage->Show(0);
		POS pos = m_oUIHistoryPage.Find(pPage);

		if (pos != NULL)
		{
			m_oUIHistoryPage.RemoveAt(pos);
		}

		CUIWndPage *pPageDelete = pPage;
		pPage->ClosePage();

		pPage = (CUIWndPage*)m_oUIHistoryPage.GetTail();

		if (pPage != NULL)
		{
			m_pActivePage = pPage;
			pPage->Show(1);
			pPageDelete->Destroy();
			delete pPageDelete;
		}
		else
		{
			m_pActivePage = NULL;
			//AfxGetApp()->PostThreadMessage(WM_QUIT, 0, 0);
			if (bPostExitMsg)
			{
				CUIWndThread::PostProcMainWndMsg(WM_EXITINSTANCE, 0, 0);
			}
		}
	}
	else
	{
	}

	return TRUE;
}



BOOL CUIWndMain::ShowPage(const CString &strPageID,long nShow)
{
	CUIWndPage *pPage = m_pPagesDef->FindPage(strPageID);
	BOOL bTrue = TRUE;
	CUIWndPage *pPageHide = NULL;

	if (pPage != NULL)
	{
		if (pPage != m_pActivePage)
		{
			pPageHide = m_pActivePage;

			if (pPage->LoadPage() )
			{
				pPage->Show(nShow);
				m_oUIHistoryPage.AddTail(pPage);
				m_pActivePage = pPage;
				m_pActivePage->m_pWindow->SetActiveWindow();//将当前界面拥有焦点
			}
			else
			{
				bTrue = FALSE;
			}

			if (pPageHide != NULL)
			{
				pPageHide->Show(0);
			}
		}
		else
		{
		}
	}
	else
	{
		bTrue = FALSE;
	}

	if (CUIWndRegister::g_nUIWndRegisterRef == 0)
	{
		AfxMessageBox(_T("你使用的系统没有注册!"), MB_OK | MB_ICONWARNING);
		CUIWndThread::PostProcMainWndMsg(WM_EXITINSTANCE, 0, 0);
	}

	return bTrue;
}