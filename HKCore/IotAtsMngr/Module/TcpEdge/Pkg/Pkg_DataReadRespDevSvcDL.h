//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_DataReadRespDevSvcDL.h  CPkg_DataReadRespDevSvcDL

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "PxPkgDataBase.h"


class CPkg_DataReadRespDevSvcDL : public CPxPkgDataBase
{
public:
	CPkg_DataReadRespDevSvcDL();
	virtual ~CPkg_DataReadRespDevSvcDL();


	CString  m_strDataRefer;
	CString  m_strValue;
	CString  m_strAngle;
	CString  m_strTimeStamp;
	CString  m_strQuality;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPKG_DATAREADRESPDEVSVCDL;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPkg_DataReadRespDevSvcDLKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPkg_DataReadRespDevSvcDLKey();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);
};

