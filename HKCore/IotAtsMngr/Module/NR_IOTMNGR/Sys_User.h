//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Sys_User.h  CSys_User

#pragma once

#include "NR_IOTMNGRGlobal.h"



class CSys_User : public CExBaseObject
{
public:
	CSys_User();
	virtual ~CSys_User();


	long  m_nUser_Id;
	long  m_nDept_Id;
	CString  m_strUser_Name;
	CString  m_strNick_Name;
	CString  m_strUser_Type;
	CString  m_strEmail;
	CString  m_strPhonenumber;
	CString  m_strSex;
	CString  m_strAvatar;
	CString  m_strPassword;
	CString  m_strStatus;
	CString  m_strDel_Flag;
	CString  m_strLogin_Ip;
	SYSTEMTIME  m_tmLogin_Date;
	CString  m_strCreate_By;
	SYSTEMTIME  m_tmCreate_Time;
	CString  m_strUpdate_By;
	SYSTEMTIME  m_tmUpdate_Time;
	CString  m_strRemark;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CSYS_USER;   }
	virtual BSTR GetXmlElementKey()  {      return CNR_IOTMNGRXmlRWKeys::CSys_UserKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nUser_Id;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CSys_UserKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::User_IdKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nUser_Id);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nUser_Id = pRecordset->GetInsertId();     }

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

