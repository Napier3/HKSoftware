//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteRegHis.h  CStt_RemoteRegHis

#pragma once

#include "RemoteCtrlMngrGlobal.h"

#include "Stt_RemoteUserHis.h"
#include "../../SttCmd/SttRemoteCmd.h"
#include "../../SttSocket/Cloud/SttCloudServerClientSocketBase.h"

#define ID_STT_REGISTER_MODE_TEST		0
#define ID_STT_REGISTER_MODE_ASSIST		1

class CStt_RemoteRegHis : public CExBaseList
{
public:
	CStt_RemoteRegHis();
	virtual ~CStt_RemoteRegHis();


	long  m_nIndex_Register;
	CString  m_strSN_TestApp;
	CString  m_strModel_TestApp;
	CString  m_strModel_Dv;
	CString  m_strName_Cop;
	CString  m_strName_User;
	CString  m_strCode_Register;
	SYSTEMTIME  m_tmTm_Register;
	SYSTEMTIME  m_tmTm_UnRegister;
	long  m_nMode_Register;
	CString  m_strDescription;
	CString  m_strPath_HisFiles;

	CString  m_strVer_PpMmsEngine;
	CString  m_strVer_PpEngine;
	CString  m_strVer_SttTestStudio;
	CString  m_strVer_SttTestCntr;
	CString  m_strVer_Iec61850Config;
	CString  m_strVer_DvmTest;
	CString  m_strVer_SmartTest;
	CString  m_strVer_TestServer;

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTT_REMOTEREGHIS;   }
	virtual BSTR GetXmlElementKey()  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegHisKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Register;     }
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegHisKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserHisKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::Index_RegisterKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Register);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset);
	virtual CExBaseObject* DB_CreateNewChild();

//私有成员变量
private:

//私有成员变量访问方法
public:
	CSttCloudServerClientSocketBase *m_pRef_Socket;
	CSttCloudServerClientSocketBase * GetRefSocket()	{	return m_pRef_Socket;	}
	void SetRefSocket(CSttCloudServerClientSocketBase *pRef_Socket);

//属性变量访问方法
public:
	BOOL IsRegister_Test()	{	return (m_nMode_Register == ID_STT_REGISTER_MODE_TEST);	}
	BOOL IsRegister_Assist()	{	return (m_nMode_Register == ID_STT_REGISTER_MODE_ASSIST);	}

	void GetRegDetail(CString &strRegDetail);

	void AnalysisRegisterAttr(CSttRemoteCmd &oRemoteCmd,CSttCloudServerClientSocketBase *pRef_Socket
		,const CString &strRootPath);

	void InitDvmData(CDvmData &oData);
};

