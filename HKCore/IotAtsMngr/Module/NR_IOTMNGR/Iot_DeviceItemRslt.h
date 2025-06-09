//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_DeviceItemRslt.h  CIot_DeviceItemRslt

#pragma once

#include "NR_IOTMNGRGlobal.h"



class CIot_DeviceItemRslt : public CExBaseObject
{
public:
	CIot_DeviceItemRslt();
	virtual ~CIot_DeviceItemRslt();


	long  m_nIndex_Item_Rslt;
	long  m_nIndex_Test;
	long  m_nIndex_Device;
	long  m_nIndex_Item;
	long  m_nState;
	long  m_nRsltjdg;
	CString  m_strRsltdsc;
	CString  m_strFile_Report;
	CString  m_strFile_Pkgs;
	long  m_nSelect_State;
	long  m_nIndex_Bench;
	CString  m_strFile_Report_S;
	CString  m_strFile_Pkgs_S;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICEITEMRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CNR_IOTMNGRXmlRWKeys::CIot_DeviceItemRsltKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Item_Rslt;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CIot_DeviceItemRsltKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::Index_Item_RsltKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Item_Rslt);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Item_Rslt = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

