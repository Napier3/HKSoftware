#include "stdafx.h"
#include "IotTestControlBase.h"

CIotTestControlBase::CIotTestControlBase()
{
	m_pRTTaskBatchRef = NULL;

	m_hMsgWnd = 0;
	m_nMsg = 0;
	m_hSysMsgWnd = 0;
	m_nSysMsg = 0;
}

CIotTestControlBase::~CIotTestControlBase()
{
	if (m_pRTTaskBatchRef != NULL)
	{
		delete m_pRTTaskBatchRef;
		m_pRTTaskBatchRef = NULL;
	}
}

CDvmDataset *CIotTestControlBase::GetDeviceAttr()
{
	if (m_pRTTaskBatchRef == NULL)
	{
		return NULL;
	}

	if (m_pRTTaskBatchRef->m_pDvmDeviceRef == NULL)
	{
		return NULL;
	}
	
	return m_pRTTaskBatchRef->m_pDvmDeviceRef->GetDeviceAttrs();
}

BOOL CIotTestControlBase::GetDeviceAttrValueByID(const CString &strID,CString &strValue)
{
	CDvmDataset *pDeviceAttr = GetDeviceAttr();
	if (pDeviceAttr == NULL)
	{
		return FALSE;
	}

	CDvmData *pFind = (CDvmData *)pDeviceAttr->FindByID(strID);
	if (pFind == NULL)
	{
		return FALSE;
	}

	strValue = pFind->m_strValue;
	return TRUE;
}

BOOL CIotTestControlBase::GetDeviceAttrValueByID(const CString &strID,long &nValue)
{
	CString strValue = _T("");
	BOOL bRet = GetDeviceAttrValueByID(strID,strValue);
	if (!bRet)
	{
		return FALSE;
	}
	nValue = CString_To_long(strValue);
	return TRUE;
}

CDvmDataset *CIotTestControlBase::FindDataset(const CString &strDatasetID)
{
	if (m_pRTTaskBatchRef == NULL)
	{
		return NULL;
	}

	if (m_pRTTaskBatchRef->m_pDvmDeviceRef == NULL)
	{
		return NULL;
	}

	return m_pRTTaskBatchRef->m_pDvmDeviceRef->FindDataset(strDatasetID);
}

//////////////////////////////////////

BOOL InitMySqlApp(CMySqlBaseApp &oMySqlBaseApp)
{
	CDBServerInfoBase oServerInfo;
	oServerInfo.m_strHostIp = _T("127.0.0.1");
	oServerInfo.m_strDbName = _T("ats_testmngr");
	oServerInfo.m_strUserName = _T("root");
	oServerInfo.m_strPasswd = _T("123456");
	oServerInfo.m_iPort = 3306;
	return oMySqlBaseApp.InitMySqlDB(oServerInfo);
}

CString GetIDFromPath(const CString &strPath,char chSeperator)
{
	CString strID;
	long nPos = strPath.ReverseFind(chSeperator);
	if (nPos >= 0)
	{
		strID = strPath.Mid(nPos + 1);
	}
	else
	{
		strID = strPath;
	}

	return strID;
}

void CommVm_PostDeviceSysMessage(CIotTestControlBase *pTestCtrl, WPARAM wParam, LPARAM lParam)
{
	ASSERT(pTestCtrl != NULL);

	HWND hWnd = (HWND)pTestCtrl->m_hSysMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 【%08x】 不是窗口【Sys】"), pTestCtrl->m_hSysMsgWnd);
		return;
	}

	::PostMessage(hWnd, pTestCtrl->m_nSysMsg, wParam, lParam);
}

void CommVm_PostDeviceCommCmdMessage(CIotTestControlBase *pTestCtrl, WPARAM wParam, LPARAM lParam)
{
	ASSERT(pTestCtrl != NULL);

	HWND hWnd = (HWND)pTestCtrl->m_hMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 【%08x】 不是窗口【CommCmd】"), pTestCtrl->m_hMsgWnd);
		return;
	}

	::PostMessage(hWnd, pTestCtrl->m_nMsg, wParam, lParam);
}