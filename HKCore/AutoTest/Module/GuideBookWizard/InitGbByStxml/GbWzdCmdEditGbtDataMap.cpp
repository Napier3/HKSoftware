#include "stdafx.h"
#include "GbWzdCmdEditGbtDataMap.h"
#include "..\..\XLanguageResourceAts.h"
#include "..\GuideBookWizard.h"

CGbWzdCmdEditGbtDataMap::CGbWzdCmdEditGbtDataMap()
{
	m_strName = /*_T("�������ģ��")*/g_sLangTxt_SaveTestTem;
	m_strID = _T("Save");
}


CGbWzdCmdEditGbtDataMap::~CGbWzdCmdEditGbtDataMap()
{
	
}


long CGbWzdCmdEditGbtDataMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmdEditGbtDataMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmd::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CGbWzdCmdEditGbtDataMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmd::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

BSTR CGbWzdCmdEditGbtDataMap::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdEditGbtDataMapKey();
}


BOOL CGbWzdCmdEditGbtDataMap::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmdEditGbtDataMap::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmdEditGbtDataMap::Clone()
{
	CGbWzdCmdEditGbtDataMap *pNew = new CGbWzdCmdEditGbtDataMap();
	Copy(pNew);
	return pNew;
}


BOOL CGbWzdCmdEditGbtDataMap::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);
	
	CFrameWnd* pFrameWnd = GetMaiFrame();
	ShowGbWzdMsg(/*_T("������ģ��Ľӿڣ�������ģ�嵽ģ����")*/g_sLangTxt_SetSubTemInterface);

	return TRUE;
}

void CGbWzdCmdEditGbtDataMap::GetCmdInfor(CString &strText)
{
	strText = /*_T("������ģ��Ľӿڣ�������ģ�嵽ģ����")*/g_sLangTxt_SetSubTemInterface;
	//CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdEditGbtDataMap::IsCmdFinish()
{
	m_nCmdExecState = GBWZDCMD_STATE_FINISH;
	return TRUE;
}

