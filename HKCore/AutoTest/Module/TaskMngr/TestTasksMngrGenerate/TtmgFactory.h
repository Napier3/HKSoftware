//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgFactory.h  CTtmgFactory

#pragma once

#include "TestTasksMngrGenerateGlobal.h"



class CTtmgFactory : public CExBaseObject
{
public:
	CTtmgFactory();
	virtual ~CTtmgFactory();


	CString  m_strCode;
	CString  m_strOwnDef;
	CString  m_strHdVer;
//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGFACTORY;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgFactoryKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

CTtmgFactory* TTMG_FindFactory(const CString &strFactory);
