//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_AppGetConfigResp_AppCfg.h  CPkg_AppGetConfigResp_AppCfg

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"

#include "TcpEdgePkgCfgCpu.h"
#include "TcpEdgePkgCfgMem.h"

class CPkg_AppGetConfigResp_AppCfg : public CPxPkgDataBase, public CPxPkgDataBaseArrayObj
{
public:
	CPkg_AppGetConfigResp_AppCfg();
	virtual ~CPkg_AppGetConfigResp_AppCfg();


	CString  m_strApp;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_APPGETCONFIGRESP_APPCFG;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_AppGetConfigResp_AppCfgKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_AppGetConfigResp_AppCfgKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);

//私有成员变量
public:
	CTcpEdgePkgCfgCpu *m_pTcpEdgePkgCfgCpu;
	CTcpEdgePkgCfgMem *m_pTcpEdgePkgCfgMem;

	CString m_strObjectName[2];
	BOOL m_bObjectMustExist[2];
//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

