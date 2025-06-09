//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_GetHisData_DevSvc.h  CPkg_GetHisData_DevSvc

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_GetHisData_DevSvc : public CPxPkgDataBase
{
public:
	CPkg_GetHisData_DevSvc();
	virtual ~CPkg_GetHisData_DevSvc();


	CString  m_strMaxNumber;
	CString  m_strInterval;
	CString  m_strEndTime;
	CString  m_strStartTime;
	CString  m_strServiceId;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_GETHISDATA_DEVSVC;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_GetHisData_DevSvcKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_GetHisData_DevSvcKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	 static CDvmDataset* ToDataset();

};

