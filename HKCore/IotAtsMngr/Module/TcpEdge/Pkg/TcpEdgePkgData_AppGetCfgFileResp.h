//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppGetCfgFileResp.h  CTcpEdgePkgData_AppGetCfgFileResp

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "TcpEdgePkgData.h"

#include "TcpEdgePkgFile.h"

class CTcpEdgePkgData_AppGetCfgFileResp : public CTcpEdgePkgData
{
public:
	CTcpEdgePkgData_AppGetCfgFileResp();
	virtual ~CTcpEdgePkgData_AppGetCfgFileResp();


	CString  m_strStatus;
	CString  m_strErrorCode;
	CString  m_strNote;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCFGFILERESP;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_AppGetCfgFileRespKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_AppGetCfgFileRespKey();     }
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);
	CTcpEdgePkgFile* GetTcpEdgePkgFile(){ return m_pTcpEdgePkgFile; }

//私有成员变量
private:
	CTcpEdgePkgFile *m_pTcpEdgePkgFile;

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

