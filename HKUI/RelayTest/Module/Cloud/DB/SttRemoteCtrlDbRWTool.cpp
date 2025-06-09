#include "stdafx.h"
#include "RemoteCtrlMngrGlobal.h"
#include "SttRemoteCtrlDbRWTool.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


BOOL Stt_DeleteAllRealTimeDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	CString strTable;

	pXDbLib->StartTransaction();

	strTable = CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegRTKey();
	pXDbLib->SQLDelete(strTable , _T("") , _T("") );

	strTable = CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserRTKey();
	pXDbLib->SQLDelete(strTable , _T("") , _T("") );

	pXDbLib->Commit();

	return TRUE;
}

CStt_RemoteRegRT *Stt_InitRegisterDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
								 ,CStt_RemoteRegHis &oRemoteRegHis)
{
	pXDbLib->StartTransaction();

	//插入历史表
	CXDbQueryChildrenMask oXdbQueryMask;
	oRemoteRegHis.DB_Insert(pXDbLib,pXmlRWKeys, &oXdbQueryMask); 

	//历史表拷贝到实时表
	CStt_RemoteRegRT *pNewRT = new CStt_RemoteRegRT;
	oRemoteRegHis.CopyOwn(pNewRT);

	//插入实时表
	pNewRT->DB_Insert(pXDbLib,pXmlRWKeys, &oXdbQueryMask);

	pXDbLib->Commit();

	return pNewRT;
}

BOOL Stt_InitUnRegisterDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys,CStt_RemoteRegRT &oRemoteRegRT)
{
	//更新历史表
	CString strTable,strPK,strTmUnRegisterKey,strTmUnRegister;
	strTable = CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegHisKey();
	strPK = CRemoteCtrlMngrXmlRWKeys::Index_RegisterKey();
	strTmUnRegisterKey = CRemoteCtrlMngrXmlRWKeys::Tm_UnRegisterKey();

	GetLocalTime(&oRemoteRegRT.m_tmTm_UnRegister);
	SystemTime_To_String(oRemoteRegRT.m_tmTm_UnRegister,strTmUnRegister);

	CString strSql;
	strSql.Format(_T("update %s set %s=\"%s\" where %s=%d")
		,strTable,strTmUnRegisterKey,strTmUnRegister,strPK,oRemoteRegRT.m_nIndex_Register);

	pXDbLib->StartTransaction();

	pXDbLib->ExecuteCmd(strSql);

	//删除实时表
	strTable = CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserRTKey();
	strSql.Format(_T("delete from %s where %s=%d")
		,strTable,strPK,oRemoteRegRT.m_nIndex_Register);
	pXDbLib->ExecuteCmd(strSql);

	strTable = CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegRTKey();
	strSql.Format(_T("delete from %s where %s=%d")
		,strTable,strPK,oRemoteRegRT.m_nIndex_Register);
	pXDbLib->ExecuteCmd(strSql);

	pXDbLib->Commit();

	return TRUE;
}

BOOL Stt_UpdateUserDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
				  ,CStt_RemoteRegRT *pRemoteRegRT,CStt_RemoteRegRT &oUserList)
{	
	CStt_RemoteUserRT *pUserRT = NULL;
	CStt_RemoteUserRT *pMatchUserRT = NULL;
	CXDbQueryChildrenMask oXdbQueryMask;

	pXDbLib->StartTransaction();

	POS pos = oUserList.GetHeadPosition();
	while(pos != NULL)
	{
		pUserRT = (CStt_RemoteUserRT *)oUserList.GetNext(pos);

		pMatchUserRT = pRemoteRegRT->FindMacthUser(pUserRT);

		if (pMatchUserRT != NULL)
		{//已存在
			if (pMatchUserRT->m_nID_Authority != pUserRT->m_nID_Authority)
			{//实时用户权限更改
				pMatchUserRT->m_nID_Authority = pUserRT->m_nID_Authority;
				pMatchUserRT->UpdateDB_Authority(pXDbLib,pXmlRWKeys);
			}
		}
		else
		{//新用户,则插入历史、实时用户记录
			CStt_RemoteUserHis oRemoteUserHis;

			pUserRT->CStt_RemoteUserHis::CopyOwn(&oRemoteUserHis);
			oRemoteUserHis.m_nIndex_User = 0;
			oRemoteUserHis.m_nIndex_Register = pRemoteRegRT->m_nIndex_Register;

			CString strSql;
			oRemoteUserHis.GetDB_SelectSql(strSql);
			oRemoteUserHis.DB_Insert(pXDbLib,pXmlRWKeys, strSql); 

			CStt_RemoteUserRT *pNewUserRT = new CStt_RemoteUserRT;
			oRemoteUserHis.CopyOwn(pNewUserRT);
			pNewUserRT->DB_Insert(pXDbLib,pXmlRWKeys, &oXdbQueryMask);

			pRemoteRegRT->AddNewChild(pNewUserRT);
		}
	}

	pos = pRemoteRegRT->GetHeadPosition();
	while(pos != NULL)
	{
		pUserRT = (CStt_RemoteUserRT *)pRemoteRegRT->GetNext(pos);

		pMatchUserRT = oUserList.FindMacthUser(pUserRT);

		if (pMatchUserRT != NULL)
		{//已存在
			continue;
		}

		//多余的用户删除
		pUserRT->DB_Delete_Own(pXDbLib,pXmlRWKeys);
		pRemoteRegRT->Delete(pUserRT);
	}

	pXDbLib->Commit();

	return TRUE;
}