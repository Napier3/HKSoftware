//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
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

//˽�г�Ա����
public:
	CTcpEdgePkgCfgCpu *m_pTcpEdgePkgCfgCpu;
	CTcpEdgePkgCfgMem *m_pTcpEdgePkgCfgMem;

	CString m_strObjectName[2];
	BOOL m_bObjectMustExist[2];
//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

