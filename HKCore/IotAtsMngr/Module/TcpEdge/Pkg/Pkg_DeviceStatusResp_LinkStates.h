//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_DeviceStatusResp_LinkStates.h  CPkg_DeviceStatusResp_LinkStates

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_DeviceStatusResp_LinkStates : public CPxPkgDataBase
{
public:
	CPkg_DeviceStatusResp_LinkStates();
	virtual ~CPkg_DeviceStatusResp_LinkStates();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_DEVICESTATUSRESP_LINKSTATES;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_DeviceStatusResp_LinkStatesKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_DeviceStatusResp_LinkStatesKey();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

