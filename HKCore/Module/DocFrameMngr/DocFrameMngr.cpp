#include "StdAfx.h"
#include "DocFrameMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDocFrameObject::CDocFrameObject(CMultiDocTemplate *pDocTempRef, CMDIChildWndEx *pFrameRef, CDocument *pDocRef, const CString &strName, const CString &strID)
{
	m_pDocTempRef = pDocTempRef;
	m_pFrameRef   = pFrameRef;
	m_pDocRef     = pDocRef;
	m_strName     = strName;
	m_strID       = strID;
	m_pDataRef    = NULL;
}

CDocFrameObject::~CDocFrameObject()
{

}

BOOL CDocFrameObject::IsDataClassID(UINT nClassID)
{
	if (m_pDataRef == NULL)
	{
		return FALSE;
	}

	return (m_pDataRef->GetClassID() == nClassID);
}


//////////////////////////////////////////////////////////////////////////
//

CDocFrameMngr* CDocFrameMngr::g_pDocFrameMngr = NULL;
long CDocFrameMngr::g_nDocFrameMngrRef = 0;

CDocFrameMngr* CDocFrameMngr::Create()
{
	g_nDocFrameMngrRef++;

	if (g_nDocFrameMngrRef == 1)
	{
		g_pDocFrameMngr = new CDocFrameMngr();
	}

	return g_pDocFrameMngr;
}

void CDocFrameMngr::Release()
{
	g_nDocFrameMngrRef--;

	if (g_nDocFrameMngrRef == 0)
	{
		delete g_pDocFrameMngr;
		g_pDocFrameMngr = NULL;
	}
}

CDocFrameMngr* CDocFrameMngr::GetDocFrameMngr()
{
	ASSERT (g_pDocFrameMngr != NULL);

	return g_pDocFrameMngr;
}

CDocFrameMngr::CDocFrameMngr(void)
{
	
}

CDocFrameMngr::~CDocFrameMngr(void)
{
}

CDocFrameObject* CDocFrameMngr::AddDocFrame(CMultiDocTemplate *pDocTempRef, CMDIChildWndEx *pFrameRef, CDocument *pDocRef, const CString &strName, const CString &strID, CExBaseObject *pDataRef)
{
	CDocFrameObject *pFind = NULL;
	
	if (strID.GetLength() > 0)
	{
		pFind = (CDocFrameObject*)g_pDocFrameMngr->FindByID(strID);
	}

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CDocFrameObject(pDocTempRef, pFrameRef, pDocRef, strName, strID);
	pFind->m_pDataRef = pDataRef;
	g_pDocFrameMngr->AddNewChild(pFind);
	pDocRef->SetTitle(strName);

	return pFind;
}

void CDocFrameMngr::CloseFrame(CMDIChildWndEx *pFrameRef, BOOL bCloseFrame)
{
	if (bCloseFrame)
	{
		pFrameRef->PostMessage(WM_CLOSE);
	}

	CDocFrameObject *p = NULL;
	POS pos = g_pDocFrameMngr->GetHeadPosition();
	POS posDel = pos;

	while (pos != NULL)
	{
		posDel = pos;
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);

		if (p->m_pFrameRef == pFrameRef)
		{
			g_pDocFrameMngr->RemoveAt(posDel);
			delete p;
			break;
		}
	}
}

void CDocFrameMngr::CloseFrameEx(CExBaseObject *pDataRef, BOOL bCloseFrame)
{
	CDocFrameObject *p = NULL;
	POS pos = g_pDocFrameMngr->GetHeadPosition();
	POS posDel = pos;

	while (pos != NULL)
	{
		posDel = pos;
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);

		if (p->m_pDataRef != pDataRef)
		{
			continue;
		}

		if (bCloseFrame)
		{
			p->m_pFrameRef->PostMessage(WM_CLOSE);
		}

		g_pDocFrameMngr->RemoveAt(posDel);
		delete p;
		break;
	}
}

void CDocFrameMngr::CloseDocFrame(const CString &strID)
{
	CDocFrameObject *pFind = (CDocFrameObject*)g_pDocFrameMngr->FindByID(strID);

	if (pFind == NULL)
	{
		return;
	}

	g_pDocFrameMngr->Delete(pFind);
}

//2020-10-13  lijunqing
void CDocFrameMngr::CloseDocFrame(CDocFrameObject *pDocFrameObject)
{
	g_pDocFrameMngr->Delete(pDocFrameObject);
}

CDocFrameObject* CDocFrameMngr::FindDocFrameObject(const CString &strID)
{
	CDocFrameObject *pFind = (CDocFrameObject*)g_pDocFrameMngr->FindByID(strID);

	return pFind;
}

CDocFrameObject* CDocFrameMngr::FindDocFrameObject(CDocument *pDoc)
{
	CDocFrameObject *pFind = NULL;
	CDocFrameObject *p = NULL;
	POS pos = g_pDocFrameMngr->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);

		if (p->m_pDocRef == pDoc)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDocFrameObject* CDocFrameMngr::FindDocFrameObject(CMDIChildWndEx *pFrame)
{
	CDocFrameObject *pFind = NULL;
	CDocFrameObject *p = NULL;
	POS pos = g_pDocFrameMngr->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);

		if (p->m_pFrameRef == pFrame)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDocFrameObject* CDocFrameMngr::FindDocFrameObject(CExBaseObject *pDataRef)
{
	CDocFrameObject *pFind = NULL;
	CDocFrameObject *p = NULL;
	POS pos = g_pDocFrameMngr->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);

		if (p->m_pDataRef == pDataRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDocFrameObject* CDocFrameMngr::FindDocFrameObject(CExBaseObject *pDataRef, CDocTemplate *pTemplate)
{
	CDocFrameObject *pFind = NULL;
	CDocFrameObject *p = NULL;
	POS pos = g_pDocFrameMngr->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);

		if (p->m_pDataRef == pDataRef && p->m_pDocTempRef == pTemplate)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDocFrameObject* CDocFrameMngr::FindDocFrameObject_Has(const CString &strID)
{
	CDocFrameObject *pFind = (CDocFrameObject*)g_pDocFrameMngr->FindByID(strID);

	POS pos = g_pDocFrameMngr->GetHeadPosition();
	CDocFrameObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);

		if (p->m_strID.Find(strID) >= 0)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

long CDocFrameMngr::GetDocFrameCount()
{
	ASSERT (g_pDocFrameMngr != NULL);
	return g_pDocFrameMngr->GetCount();
}

CDocFrameObject* CDocFrameMngr::GetDocFrame(long nIndex)
{
	ASSERT (g_pDocFrameMngr != NULL);
	return (CDocFrameObject*)g_pDocFrameMngr->GetAtIndex(nIndex);
}	

//20180914 lijq
CMDIChildWndEx* CDocFrameMngr::FindDocFrame(const CString &strID)
{
	CDocFrameObject *pFind = FindDocFrameObject(strID);

	if (pFind == NULL)
	{
		return NULL;
	}

	return pFind->m_pFrameRef;
}

CMDIChildWndEx* CDocFrameMngr::FindDocFrame(CExBaseObject *pDataRef)
{
	CDocFrameObject *pFind = FindDocFrameObject(pDataRef);

	if (pFind == NULL)
	{
		return NULL;
	}

	return pFind->m_pFrameRef;
}

CMDIChildWndEx* CDocFrameMngr::FindDocFrame(CExBaseObject *pDataRef, CDocTemplate *pTemplate)
{
	CDocFrameObject *pFind = FindDocFrameObject(pDataRef, pTemplate);

	if (pFind == NULL)
	{
		return NULL;
	}

	return pFind->m_pFrameRef;
}

CMDIChildWndEx* CDocFrameMngr::FindDocFrame(CDocument *pDoc)
{
	CDocFrameObject *pFind = FindDocFrameObject(pDoc);

	if (pFind == NULL)
	{
		return NULL;
	}

	return pFind->m_pFrameRef;
}

CMDIChildWndEx* CDocFrameMngr::FindDocFrame_Has(const CString &strID)
{
	CDocFrameObject *pFind = FindDocFrameObject_Has(strID);

	if (pFind == NULL)
	{
		return NULL;
	}

	return pFind->m_pFrameRef;
}

CExBaseObject* CDocFrameMngr::FindRefData(CMDIChildWndEx *pFrame)
{
	CDocFrameObject *pFind = g_pDocFrameMngr->FindDocFrameObject(pFrame);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (pFind->m_pDataRef == NULL)
	{
		return NULL;
	}

	return pFind->m_pDataRef;
}

void CDocFrameMngr::CloseAllFrame()
{
	CDocFrameObject *p = NULL;
	POS pos = g_pDocFrameMngr->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDocFrameObject *)g_pDocFrameMngr->GetNext(pos);
		p->m_pFrameRef->PostMessage(WM_CLOSE);
	}

	g_pDocFrameMngr->DeleteAll();
}

//////////////////////////////////////////////////////////////////////////
//

CDocument* docfrm_OpenDocTemplate(CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame, const CString &strFile)
{
	CDocument *pDoc = NULL;
	
	if (strFile.GetLength() > 0)
	{
		if (strFile.GetLength() > MAX_PATH)
		{
			pDoc = pDocTemplate->OpenDocumentFile(NULL);
		}
		else
		{
			pDoc = pDocTemplate->OpenDocumentFile(strFile);
		}
	}
	else
	{
		pDoc = pDocTemplate->OpenDocumentFile(NULL);
	}

	POSITION	pos = pDoc->GetFirstViewPosition();
	*pView=pDoc->GetNextView(pos);
	ASSERT(*pView != NULL);
	*pFrame = (CMDIChildWndEx*)(*pView)->GetParentFrame();
	ASSERT(*pFrame != NULL);

	return pDoc;
}

CDocument* docfrm_OpenDocTemplateEx(CExBaseObject *pDataRef, CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame, const CString &strFile)
{
	CDocument *pDoc = docfrm_OpenDocTemplate(pDocTemplate, pView, pFrame, strFile);
	CDocFrameObject *pDocFrmObj = CDocFrameMngr::AddDocFrame(pDocTemplate, *pFrame, pDoc, strFile, strFile);
	
	pDocFrmObj->m_pDataRef = pDataRef;

	return pDoc;
}

CDocument* docfrm_OpenDocTemplateEx(CDocFrameObject **ppDocFrmObj, CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame, const CString &strFile)
{
	CDocument *pDoc = docfrm_OpenDocTemplate(pDocTemplate, pView, pFrame, strFile);
	*ppDocFrmObj = CDocFrameMngr::AddDocFrame(pDocTemplate, *pFrame, pDoc, strFile, strFile);

	return pDoc;
}

CDocument* docfrm_OpenDocTemplate(CMultiDocTemplate *pDocTemplate, CExBaseObject *pDataRef)
{
	CMDIChildWndEx *pFrame = CDocFrameMngr::FindDocFrame(pDataRef);

	if (pFrame != NULL)
	{
		pFrame->ActivateFrame();
		return NULL;
	}

	CView *pView = NULL;
	CDocument *pDoc = docfrm_OpenDocTemplateEx(pDataRef, pDocTemplate, &pView, &pFrame);
	pDoc->UpdateAllViews(NULL, (LPARAM)pDataRef, NULL);
	pDoc->SetTitle(pDataRef->m_strName);

	return pDoc;
}

