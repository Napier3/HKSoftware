// CXKeyDbDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XKeyDBUiGlobal.h"
#include "..\..\XLanguage\XLanguageMngr.h"
CXKeyEditDlgBase::CXKeyEditDlgBase(CWnd* pParent /*=NULL*/)
:CDynDialogEx(pParent)
{
	m_nXKeyEditDlgMode = XKEYEDITDLG_MODE_NONE;
	m_pXKey = NULL;
	m_pKeyParent = NULL;
}

CXKeyEditDlgBase::~CXKeyEditDlgBase()
{
	if (m_nXKeyEditDlgMode == XKEYEDITDLG_MODE_EDIT)
	{
		delete m_pXKey;
		m_pXKey = NULL;
	}
}

int CXKeyEditDlgBase::NewKey(CExBaseObject *pKey)
{
	ASSERT (pKey != NULL);
	m_pXKeySrc = NULL;

	if (pKey == NULL)
	{
		return IDCANCEL;
	}

	m_nXKeyEditDlgMode = XKEYEDITDLG_MODE_NEW;
	m_pXKey = pKey;
	m_pKeyParent = (CExBaseList *)pKey->GetParent();

	int nRet = DoModal();
	
	return nRet;
}

int CXKeyEditDlgBase::EditKey(CExBaseObject *pKey)
{
	ASSERT (pKey != NULL);

	if (pKey == NULL)
	{
		return IDCANCEL;
	}

	m_pXKeySrc = pKey;
	m_nXKeyEditDlgMode = XKEYEDITDLG_MODE_EDIT;
	m_pKeyParent = (CExBaseList *)pKey->GetParent();
	m_pXKey = (CExBaseObject*)pKey->Clone();

	int nRet = DoModal();

	return nRet;
}

BOOL CXKeyEditDlgBase::ValidateKey(const CString &strName, const CString &strID)
{
	ASSERT (m_pXKey != NULL);
	ASSERT( m_pKeyParent != NULL);

	CXKeyDB *pKeyDb = (CXKeyDB*)m_pKeyParent;

	CExBaseObject *pFind = pKeyDb->FindByKeyName(strName);
	CString strMsg;

	if (pFind != NULL && pFind != m_pXKeySrc)
	{
		strMsg.Format(/*_T("������ͬ���ƵĹؼ��֡�%s��")*/g_sLangTxt_KeySameId, strName);
		MessageBox(strMsg, /*_T("ע��")*/g_sLangTxt_Attention, MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	pFind = pKeyDb->FindByID(strID);

	if (pFind != NULL && pFind != m_pXKeySrc)
	{
		strMsg.Format(/*_T("������ͬID�Ĺؼ��֡�%s��")*/g_sLangTxt_KeySameId, strID);
		MessageBox(strMsg, /*_T("ע��")*/g_sLangTxt_Attention, MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}
