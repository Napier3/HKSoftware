//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_RTDeviceHisDataTitle.h  CIot_RTDeviceHisDataTitle

#pragma once

#include "Iot_AtsMngrGlobal.h"

//�����豸+�����ǵ���Ҫ���������ߵ����ݵĶ���
//��������������ơ����ݱ�ʶ�����ݣ�
//���ݸñ��еĶ��壬��ʵʱ������ʷ����ȥ������

class CIot_RTDeviceHisDataTitle : public CExBaseObject
{
public:
	CIot_RTDeviceHisDataTitle();
	virtual ~CIot_RTDeviceHisDataTitle();


	long  m_nIndex_His_Data_Title;
	long  m_nIndex_Device_Type;
	CString m_strDataName;
	CString m_strDataID;
	CString m_strData;
	CString m_strDataUnit;
	
	//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_RTDEVICEHISDATATITLE;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataTitleKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_His_Data_Title;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataTitleKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_His_Data_TitleKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_His_Data_Title);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_His_Data_Title = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:

};

