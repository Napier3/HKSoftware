#include "stdafx.h"
#include "GbWzdCmdSelectStxmlFile.h"
#include "..\XLanguageResourceAts.h"
#include "GuideBookWizard.h"

CGbWzdCmdSelectStxmlFile::CGbWzdCmdSelectStxmlFile()
{
	m_strName = /*_T("ѡ�������ģ��")*/g_sLangTxt_SelTestSubTem;
	m_strID = _T("SelectStxmlFile");
}


CGbWzdCmdSelectStxmlFile::~CGbWzdCmdSelectStxmlFile()
{
	
}


long CGbWzdCmdSelectStxmlFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmdSelectStxmlFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmd::XmlReadOwn(oNode,pXmlRWKeys);
	CGbWzdToolXmlRWKeys *pGbXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbWzdCmdSelectStxmlFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmd::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pGbXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BSTR CGbWzdCmdSelectStxmlFile::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdSelectStxmlFileKey();
}


BOOL CGbWzdCmdSelectStxmlFile::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmdSelectStxmlFile::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmdSelectStxmlFile::Clone()
{
	CGbWzdCmdSelectStxmlFile *pNew = new CGbWzdCmdSelectStxmlFile();
	Copy(pNew);
	return pNew;
}


BOOL CGbWzdCmdSelectStxmlFile::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);
	ShowGbWzdMsg(/*_T("ѡ����ģ�壬�����ť���򿪡������ģ�壬�����ȡ������ť����ѡ��")*/g_sLangTxt_SelSubTem);

	//�Զ�ƴ��ģ��  shaol  2019.04.24
	if  (CGuideBookWizard::IsGbWzdAuto() && CGuideBookWizard::IsGbWzdAuto_Auto())
	{
		CFrameWnd *pFrameWnd = GetMaiFrame();
		pFrameWnd->PostMessage(WM_EXEC_GBWZD_EXEC_NEXT, 0, 0);
	}

	return TRUE;
}

void CGbWzdCmdSelectStxmlFile::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdSelectStxmlFile::IsCmdFinish()
{
	m_nCmdExecState = GBWZDCMD_STATE_FINISH;
	return TRUE;
}

