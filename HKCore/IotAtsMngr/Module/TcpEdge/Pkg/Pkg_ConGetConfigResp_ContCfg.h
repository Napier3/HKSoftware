//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ConGetConfigResp_ContCfg.h  CPkg_ConGetConfigResp_ContCfg

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"
#include "TcpEdgePkgCfgCpu.h"
#include "TcpEdgePkgCfgMem.h"
#include "TcpEdgePkgCfgDisk.h"

class CPkg_ConGetConfigResp_ContCfg : public CPxPkgDataBase, public CPxPkgDataBaseArrayObj
{
public:
	CPkg_ConGetConfigResp_ContCfg();
	virtual ~CPkg_ConGetConfigResp_ContCfg();


	CString  m_strContainer;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_CONGETCONFIGRESP_CONTCFG;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_ConGetConfigResp_ContCfgKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_ConGetConfigResp_ContCfgKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);

//私有成员变量
public:
	CTcpEdgePkgCfgCpu *m_pTcpEdgePkgCfgCpu;
	CTcpEdgePkgCfgMem *m_pTcpEdgePkgCfgMem;
	CTcpEdgePkgCfgDisk *m_pTcpEdgePkgCfgDisk;

	CString m_strObjectName[3];
	BOOL m_bObjectMustExist[3];

//私有成员变量访问方法
public:
	long XmlReadJsonArray(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys, const char *string);
	long XmlWriteJsonArray(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys, const char *string);
//属性变量访问方法
public:
};

