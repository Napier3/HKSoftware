#pragma once

#include "GuideBookDefine.h"

class CStandard : public CExBaseObject
{
public:
	CStandard();
	virtual ~CStandard();

//����
public:
	CString m_strStandard;

//�����ӿ�
public:
	void SetStandard(CString strStandard) { m_strStandard = strStandard;}
	CString GetStandard() { return m_strStandard;}
	//��д���෽��
public:
	virtual UINT GetClassID()		{		return GBCLASSID_STANDARD;			}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
};