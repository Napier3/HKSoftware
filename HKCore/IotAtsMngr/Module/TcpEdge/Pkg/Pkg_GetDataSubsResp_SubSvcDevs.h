//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_GetDataSubsResp_SubSvcDevs.h  CPkg_GetDataSubsResp_SubSvcDevs

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_GetDataSubsResp_SubSvcDevs : public CPxPkgDataBase
{
public:
	CPkg_GetDataSubsResp_SubSvcDevs();
	virtual ~CPkg_GetDataSubsResp_SubSvcDevs();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBSVCDEVS;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_GetDataSubsResp_SubSvcDevsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_GetDataSubsResp_SubSvcDevsKey();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

