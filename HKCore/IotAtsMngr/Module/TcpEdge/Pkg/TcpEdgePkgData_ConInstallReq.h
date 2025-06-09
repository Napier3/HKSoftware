//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ConInstallReq.h  CTcpEdgePkgData_ConInstallReq

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "TcpEdgePkgData.h"
#include "TcpEdgePkgCfgCpu.h"
#include "TcpEdgePkgCfgMem.h"
#include "TcpEdgePkgCfgDisk.h"


class CTcpEdgePkgData_ConInstallReq : public CTcpEdgePkgData
{
public:
	CTcpEdgePkgData_ConInstallReq();
	virtual ~CTcpEdgePkgData_ConInstallReq();


	CString  m_strContainer;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA_CONINSTALLREQ;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_ConInstallReqKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_ConInstallReqKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:
	CTcpEdgePkgCfgCpu *m_pTcpEdgePkgCfgCpu;
	CTcpEdgePkgCfgMem *m_pTcpEdgePkgCfgMem;
	CTcpEdgePkgCfgDisk *m_pTcpEdgePkgCfgDisk;

//私有成员变量访问方法
public:
	long XmlReadJsonArray(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys, const char *string);
	long XmlWriteJsonArray(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys, const char *string);

public:
	virtual CDvmDataset* ToDataset();
};

