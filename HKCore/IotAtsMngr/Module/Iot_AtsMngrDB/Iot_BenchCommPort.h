//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_BenchCommPort.h  CIot_BenchCommPort

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_BenchCommPort : public CExBaseObject
{
public:
	CIot_BenchCommPort();
	virtual ~CIot_BenchCommPort();


	long  m_nIndex_Comm;
	long  m_nIndex_Bench;
	CString  m_strType;
	CString  m_strIp;
	long  m_nPort;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_BENCHCOMMPORT;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_BenchCommPortKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Comm;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_BenchCommPortKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_CommKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Comm);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Comm = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

