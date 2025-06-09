//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDataMap.h  CXDataMap

#pragma once

#include "DataMngrGlobal.h"
#include "../System/VariantDataAddress.h"


class CXDataMap : public CExBaseObject
{
public:
	CXDataMap();
	virtual ~CXDataMap();


	CString  m_strMapID;		//������ֵ�ľ���·��	
	CVariantDataAddress m_varDataAddr;	//���й����б�����ַ

//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CXDATAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CXDataMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

