//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_DeviceModelDir.h  CIot_DeviceModelDir

#pragma once

#include "NR_IOTMNGRGlobal.h"



class CIot_DeviceModelDir : public CExBaseObject
{
public:
	CIot_DeviceModelDir();
	virtual ~CIot_DeviceModelDir();


	long  m_nIndex_Model_Dir;
	CString  m_strDir_Name;
	long  m_nParent_Index;
	SYSTEMTIME  m_tmCreate_Time;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICEMODELDIR;   }
	virtual BSTR GetXmlElementKey()  {      return CNR_IOTMNGRXmlRWKeys::CIot_DeviceModelDirKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Model_Dir;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CIot_DeviceModelDirKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::Index_Model_DirKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Model_Dir);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Model_Dir = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

