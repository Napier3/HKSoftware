//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_AppStatusResp_AppStaProc.h  CPkg_AppStatusResp_AppStaProc

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_AppStatusResp_AppStaProc : public CPxPkgDataBase
{
public:
	CPkg_AppStatusResp_AppStaProc();
	virtual ~CPkg_AppStatusResp_AppStaProc();


	CString  m_strSrvIndex;
	CString  m_strSrvName;
	CString  m_strSrvEnable;
	CString  m_strSrvStatus;
	CString  m_strCpuRate;
	CString  m_strMemUsed;
	CString  m_strStartTime;
	CString  m_strSrvNumber;
	CString  m_strCpuLmt;
	CString  m_strMemLmt;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_APPSTATUSRESP_APPSTAPROC;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_AppStatusResp_AppStaProcKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_AppStatusResp_AppStaProcKey();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);
};

