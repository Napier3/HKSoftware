//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppInstallReq.h  CTcpEdgePkgData_AppInstallReq

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "TcpEdgePkgData.h"
#include "TcpEdgePkgFile.h"
#include "TcpEdgePkgCfgCpu.h"
#include "TcpEdgePkgCfgMem.h"


class CTcpEdgePkgData_AppInstallReq : public CTcpEdgePkgData
{
public:
	CTcpEdgePkgData_AppInstallReq();
	virtual ~CTcpEdgePkgData_AppInstallReq();


	CString  m_strJobId;
	CString  m_strPolicy;
	CString  m_strContainer;
	CString  m_strApp;
	CString  m_strVersion;
	CString  m_strEnable;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLREQ;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_AppInstallReqKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_AppInstallReqKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:
	CTcpEdgePkgFile *m_pTcpEdgePkgFile;
	CTcpEdgePkgCfgCpu *m_pTcpEdgePkgCfgCpu;
	CTcpEdgePkgCfgMem *m_pTcpEdgePkgCfgMem;

//私有成员变量访问方法
public:
	virtual CDvmDataset* ToDataset();
//属性变量访问方法
public:
};

