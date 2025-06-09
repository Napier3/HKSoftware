//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeAuth.h  CEdgeAuth

#pragma once

#include "EdgeCmdMngrGlobal.h"



class CEdgeAuth : public CExBaseList
{
public:
	CEdgeAuth();
	virtual ~CEdgeAuth();

	long  m_nIndex_Auth;
	long  m_nIndex_Device;
	CString  m_strModel;
	CString  m_strSn;
	CString  m_strAuth;
	long m_nType;

//重载函数
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEAUTH;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeAuthKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Auth;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CEdgeCmdMngrXmlRWKeys::CEdge_AuthKey();     }
	virtual BSTR DB_GetTableName(CXmlRWKeys *pXmlRWKeys)				{	return CEdgeCmdMngrXmlRWKeys::CEdge_AuthKey();				}
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CEdgeCmdMngrXmlRWKeys::IndexAuthKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Auth);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Device = pRecordset->GetInsertId();     }

//私有成员变量
private:
	CString CurTimeToString();
//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CString QuenryEdgeMappingID(const CString& strSN, const CString& strModule, CXDbBaseLib *pXDbLib, CXmlRWKeys* pXmlKeys);
	CString QuenryTopoMappingID(const CString& strSN, const CString& strModule, CXDbBaseLib *pXDbLib, CXmlRWKeys* pXmlKeys);
};

