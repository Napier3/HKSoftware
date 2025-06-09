#include "stdafx.h"
#include "GbWzdCmdSave.h"
#include "..\XLanguageResourceAts.h"

CGbWzdCmdSave::CGbWzdCmdSave()
{
	m_strName = /*_T("保存测试模板")*/g_sLangTxt_SaveTestTem;
	m_strID = _T("Save");
}


CGbWzdCmdSave::~CGbWzdCmdSave()
{
	
}

long CGbWzdCmdSave::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmdSave::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmd::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CGbWzdCmdSave::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmd::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

BSTR CGbWzdCmdSave::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdSaveKey();
}


BOOL CGbWzdCmdSave::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmdSave::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmdSave::Clone()
{
	CGbWzdCmd *pNew = new CGbWzdCmd();
	Copy(pNew);
	return pNew;
}


BOOL CGbWzdCmdSave::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);
	
	CFrameWnd* pFrameWnd = GetMaiFrame();
	ShowGbWzdMsg(/*_T("保存测试模板，结束向导")*/g_sLangTxt_SaveTestTemWizardOver);
	pFrameWnd->PostMessage(WM_COMMAND, ID_FILE_SAVE, 0);//导入设备数据模型对话框

	return TRUE;
}

void CGbWzdCmdSave::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdSave::IsCmdFinish()
{
	m_nCmdExecState = GBWZDCMD_STATE_FINISH;
	return TRUE;
}

