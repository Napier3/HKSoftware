#pragma once

#include "GuideBookDefine.h"

class CValParas : public CExBaseObject
{
public:
	CValParas();
	virtual ~CValParas();

	//����
public:
	CValues *m_pValues;

	//�����ӿ�
public:
	CValues* GetValues();

	//��д���෽��
public:
	virtual UINT GetClassID()		{		return GBCLASSID_VALPARAS;		}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
};