//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_DeviceStatusResp.h  CTcpEdgePkgData_DeviceStatusResp

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "TcpEdgePkgData.h"

class CTcpEdgePkgData_DeviceStatusResp : public CTcpEdgePkgData
{
public:
	CTcpEdgePkgData_DeviceStatusResp();
	virtual ~CTcpEdgePkgData_DeviceStatusResp();


	CString  m_strCpuRate;
	CString  m_strDiskUsed;
	CString  m_strTempValue;
	CString  m_strDevDateTime;
	CString  m_strDevStDateTime;
	CString  m_strDevRunTime;
	CString  m_strLongitude;
	CString  m_strLatitude;
	CString  m_strMemUsed;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA_DEVICESTATUSRESP;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_DeviceStatusRespKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgData_DeviceStatusRespKey();     }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:

};

