//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_AppStatusResp_AppStaProcs.h  CPkg_AppStatusResp_AppStaProcs

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_AppStatusResp_AppStaProcs : public CPxPkgDataBase
{
public:
	CPkg_AppStatusResp_AppStaProcs();
	virtual ~CPkg_AppStatusResp_AppStaProcs();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_APPSTATUSRESP_APPSTAPROCS;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_AppStatusResp_AppStaProcsKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_AppStatusResp_AppStaProcsKey();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

