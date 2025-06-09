//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteUserHis.h  CStt_RemoteUserHis

#pragma once

#include "RemoteCtrlMngrGlobal.h"
#include "../../SttGlobalDef.h"
#include "../../../../Module/DataMngr/DvmData.h"

class CStt_RemoteUserHis : public CExBaseObject
{
public:
	CStt_RemoteUserHis();
	virtual ~CStt_RemoteUserHis();

	long  m_nIndex_User;
	long  m_nIndex_Register;
	CString  m_strName_Cop;
	CString  m_strName_User;
	CString  m_strIP;
	DWORD  m_nID_Test;
	CString  m_strID_Terminal;
	long  m_nID_Authority;
	CString m_strOs;
	CString m_strId_Soft;
	CString m_strVer_Soft;


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTT_REMOTEUSERHIS;   }
	virtual BSTR GetXmlElementKey()  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserHisKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_User;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserHisKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::Index_UserKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_User);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset);
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL IsTerminalType_Remote()	{	return (m_strID_Terminal == STT_TERMINAL_TYPE_REMOTE);}

	void AnalysisData(CDvmData *pData);
	void SetAuthoritys(CExBaseList *pParas);
	void SetAuthority(const CString &strModuleID, long nValue);
	void SetAuthority(long nIDAuthority, long nValue);

	BOOL GetDB_SelectSql(CString &strSql);
};

