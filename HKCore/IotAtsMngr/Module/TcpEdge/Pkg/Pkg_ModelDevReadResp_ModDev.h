//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_ModelDevReadResp_ModDev.h  CPkg_ModelDevReadResp_ModDev

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_ModelDevReadResp_ModDev : public CPxPkgDataBase
{
public:
	CPkg_ModelDevReadResp_ModDev();
	virtual ~CPkg_ModelDevReadResp_ModDev();


	CString  m_strDeviceId;
	CString  m_strDeviceDesc;
	CString  m_strStatus;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_MODELDEVREADRESP_MODDEV;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_ModelDevReadResp_ModDevKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_ModelDevReadResp_ModDevKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);

};

