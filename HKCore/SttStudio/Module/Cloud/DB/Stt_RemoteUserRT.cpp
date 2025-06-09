//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteUserRT.cpp  CStt_RemoteUserRT


#include "stdafx.h"
#include "Stt_RemoteUserRT.h"

#include "Stt_RemoteRegRT.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStt_RemoteUserRT::CStt_RemoteUserRT()
{
	//初始化属性

	//初始化成员变量
}

CStt_RemoteUserRT::~CStt_RemoteUserRT()
{
}

void CStt_RemoteUserRT::InitAfterRead()
{
}

BOOL CStt_RemoteUserRT::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStt_RemoteUserRT *p = (CStt_RemoteUserRT*)pObj;

	if(m_strName_Cop != p->m_strName_Cop)
	{
		return FALSE;
	}

	if(m_strName_User != p->m_strName_User)
	{
		return FALSE;
	}

	if(m_strIP != p->m_strIP)
	{
		return FALSE;
	}

	if(m_nID_Test != p->m_nID_Test)
	{
		return FALSE;
	}

	if(m_strID_Terminal != p->m_strID_Terminal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CStt_RemoteUserRT::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStt_RemoteUserHis::CopyOwn(pDest);

	CStt_RemoteUserRT *p = (CStt_RemoteUserRT*)pDest;

	return TRUE;
}

CBaseObject* CStt_RemoteUserRT::Clone()
{
	CStt_RemoteUserRT *p = new CStt_RemoteUserRT();
	Copy(p);
	return p;
}

CBaseObject* CStt_RemoteUserRT::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CStt_RemoteUserRT *p = new CStt_RemoteUserRT();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CStt_RemoteUserRT::CanPaste(UINT nClassID)
{
	return FALSE;
}

long CStt_RemoteUserRT::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strID_TestKey, m_nID_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strID_TerminalKey, m_strID_Terminal);
	pRecordset->GetFieldValue(pXmlKeys->m_strID_AuthorityKey, m_nID_Authority);

	return CStt_RemoteUserHis::DB_ReadFields(pRecordset, pXmlRWKeys);
	
}

long CStt_RemoteUserRT::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strID_TestKey, m_nID_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strID_TerminalKey, m_strID_Terminal);
	pRecordset->SetFieldValue(pXmlKeys->m_strID_AuthorityKey, m_nID_Authority);

	return CStt_RemoteUserHis::DB_WriteFields(pRecordset, pXmlRWKeys);
}

CExBaseObject* CStt_RemoteUserRT::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CStt_RemoteUserRT::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

BOOL CStt_RemoteUserRT::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == MNGRCLASSID_CSTT_REMOTEREGRT)
	{
		m_nIndex_Register = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

void CStt_RemoteUserRT::GetUserAuthorityDetail(CString &strUserAuthorityDetail)
{
	CStt_RemoteRegRT *pRegRT = (CStt_RemoteRegRT *)GetParent();

	if (pRegRT->GetRefSocket()->IsSocketType_Own())
	{
		strUserAuthorityDetail = _T("控制权限：");

		if((m_nID_Authority & ID_AUTHORITY_MODULE_Test) != 0)
		{
			strUserAuthorityDetail = strUserAuthorityDetail + _T("测试仪控制\r\n");
		}
		if((m_nID_Authority & ID_AUTHORITY_MODULE_ClientEngine) != 0)
		{
			strUserAuthorityDetail = strUserAuthorityDetail + _T("ClientEngine控制\r\n");
		}
		if((m_nID_Authority & ID_AUTHORITY_MODULE_Ats) != 0)
		{
			strUserAuthorityDetail = strUserAuthorityDetail + _T("自动测试控制\r\n");
		}
		if ((m_nID_Authority & ID_AUTHORITY_MASK_TESTAPP) == 0)
		{
			strUserAuthorityDetail = strUserAuthorityDetail + _T("无控制权限\r\n");
		}

		return;
	}

	strUserAuthorityDetail = _T("控制软件列表：");
	if((m_nID_Authority & ID_AUTHORITY_MODULE_PpMmsEngine) != 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("通讯程序\r\n");
	}
	if((m_nID_Authority & ID_AUTHORITY_MODULE_PpEngine) != 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("通讯程序\r\n");
	}
	if((m_nID_Authority & ID_AUTHORITY_MODULE_SttTestStudio) != 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("测试端主界面程序\r\n");
	}
	if((m_nID_Authority & ID_AUTHORITY_MODULE_SttTestCntr) != 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("单机程序\r\n");
	}
	if((m_nID_Authority & ID_AUTHORITY_MODULE_Iec61850Config) != 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("测试仪配置\r\n");
	}
	if((m_nID_Authority & ID_AUTHORITY_MODULE_DvmTest) != 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("模型比较程序\r\n");
	}
	if((m_nID_Authority & ID_AUTHORITY_MODULE_SmartTest) != 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("自动测试程序\r\n");
	}

	if ((m_nID_Authority & ID_AUTHORITY_MASK_ASSIST) == 0)
	{
		strUserAuthorityDetail = strUserAuthorityDetail + _T("无控制权限\r\n");
	}
}


BOOL CStt_RemoteUserRT::UpdateDB_Authority(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	//更新历史表
	CString strTable,strPK,strAuthorityKey;
	strTable = CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserRTKey();
	strPK = CRemoteCtrlMngrXmlRWKeys::Index_UserKey();
	strAuthorityKey = CRemoteCtrlMngrXmlRWKeys::ID_AuthorityKey();

	CString strSql;
	strSql.Format(_T("update %s set %s=\"%d\" where %s=%d")
		,strTable,strAuthorityKey,m_nID_Authority,strPK,m_nIndex_User);

	return pXDbLib->ExecuteCmd(strSql);
}

void CStt_RemoteUserRT::ClearAuthoritys(CExBaseList *pParas,CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	long nValue = 0;
	long nAuthorityChanges = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pParas->GetNext(pos);
		nValue = CString_To_long(pData->m_strValue);

		if (nValue == 1)
		{
			SetAuthority(pData->m_strID, 0);
			nAuthorityChanges++;
		}
	}

	if (nAuthorityChanges != 0)
	{
		UpdateDB_Authority(pXDbLib,pXmlRWKeys);
	}
}