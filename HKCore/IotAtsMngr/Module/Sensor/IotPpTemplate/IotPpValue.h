//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IotPpValue.h  CIotPpValue

#pragma once

#include "IOTPPGlobal.h"



class CIotPpValue : public CExBaseObject
{
public:
	CIotPpValue();
	virtual ~CIotPpValue();


	CString  m_strData_Type;
	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

